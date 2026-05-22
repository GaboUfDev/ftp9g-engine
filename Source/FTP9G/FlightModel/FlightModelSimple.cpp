// Copyright FTP9G Project. All Rights Reserved.

#include "FlightModelSimple.h"
#include "Aircraft/AircraftConfigDataAsset.h"
#include "FTP9G.h"

namespace
{
	constexpr float GravityMS2 = 9.80665f;
	constexpr float KnotsPerMS = 1.94384f;
	constexpr float FeetPerMeter = 3.28084f;
}

void UFlightModelSimple::Initialize(UAircraftConfigDataAsset* InConfig)
{
	Config = InConfig;
	LastForce_World = FVector::ZeroVector;
	LastTorque_World = FVector::ZeroVector;
	UE_LOG(LogFTP9G, Log, TEXT("FlightModelSimple initialized for %s"),
		Config ? *Config->AircraftId : TEXT("<null>"));
}

float UFlightModelSimple::AirDensityKgM3(float AltitudeMeters)
{
	const float Rho0 = 1.225f;
	const float ScaleHeight = 8500.0f;
	return Rho0 * FMath::Exp(-AltitudeMeters / ScaleHeight);
}

float UFlightModelSimple::ComputeLift(float Q, float AoARad) const
{
	if (!Config) return 0.0f;
	const float CL = Config->Aero.CL_0 + Config->Aero.CL_Alpha * AoARad;
	const float CL_Clamped = FMath::Clamp(CL, -Config->Aero.CL_Max, Config->Aero.CL_Max);
	return Q * Config->Geometry.WingAreaSqMeters * CL_Clamped;
}

float UFlightModelSimple::ComputeDrag(float Q, float CL) const
{
	if (!Config) return 0.0f;
	const float AR = Config->Geometry.AspectRatio;
	const float e = Config->Aero.OswaldEfficiency;
	const float CD_i = (CL * CL) / (PI * AR * e);
	const float CD = Config->Aero.CD_0 + CD_i;
	return Q * Config->Geometry.WingAreaSqMeters * CD;
}

float UFlightModelSimple::ComputeThrustN(float ThrottleNorm, float AirDensity) const
{
	if (!Config) return 0.0f;
	const float MaxPowerW = Config->Engine.MaxPowerHP * 745.7f;
	const float DensityRatio = AirDensity / 1.225f;
	const float AvailablePowerW = MaxPowerW * DensityRatio * FMath::Clamp(ThrottleNorm, 0.0f, 1.0f);
	const float CruiseSpeedMS = Config->Performance.CruiseSpeed_kts / KnotsPerMS;
	const float ReferenceSpeed = FMath::Max(CruiseSpeedMS, 10.0f);
	return AvailablePowerW / ReferenceSpeed;
}

void UFlightModelSimple::Step(float DeltaSeconds, const FFlightInputs& Inputs, FFlightState& InOutState)
{
	if (!Config || DeltaSeconds <= 0.0f) return;

	const float AltMeters = InOutState.AltitudeFeet / FeetPerMeter;
	const float Rho = AirDensityKgM3(AltMeters);
	const float AirspeedMS = InOutState.WorldVelocity.Size();
	const float Q = 0.5f * Rho * AirspeedMS * AirspeedMS;

	const float AoARad = FMath::DegreesToRadians(InOutState.AngleOfAttackDeg);
	const float Lift = ComputeLift(Q, AoARad);
	const float CL = Config->Aero.CL_0 + Config->Aero.CL_Alpha * AoARad;
	const float Drag = ComputeDrag(Q, CL);
	const float ThrustN = ComputeThrustN(Inputs.Throttle, Rho);

	InOutState.bStalled = FMath::Abs(InOutState.AngleOfAttackDeg) > Config->Aero.StallAngleOfAttackDeg;
	InOutState.AirspeedKts = AirspeedMS * KnotsPerMS;

	const FVector Forward = FRotationMatrix(InOutState.Attitude).GetUnitAxis(EAxis::X);
	const FVector Up = FRotationMatrix(InOutState.Attitude).GetUnitAxis(EAxis::Z);

	const FVector LiftVec = Up * Lift;
	const FVector DragVec = -InOutState.WorldVelocity.GetSafeNormal() * Drag;
	const FVector ThrustVec = Forward * ThrustN;
	const FVector Gravity = FVector(0, 0, -GravityMS2 * Config->Mass.MaxTakeoffKg);

	LastForce_World = LiftVec + DragVec + ThrustVec + Gravity;
	LastTorque_World = FVector::ZeroVector;
}
