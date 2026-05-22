// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlightModel.h"
#include "FlightModelSimple.generated.h"

UCLASS(BlueprintType)
class FTP9G_API UFlightModelSimple : public UObject, public IFlightModel
{
	GENERATED_BODY()

public:
	virtual void Initialize(UAircraftConfigDataAsset* Config) override;
	virtual void Step(float DeltaSeconds, const FFlightInputs& Inputs, FFlightState& InOutState) override;
	virtual FVector GetLastAeroForce_World() const override { return LastForce_World; }
	virtual FVector GetLastAeroTorque_World() const override { return LastTorque_World; }
	virtual FString GetModelName() const override { return TEXT("FlightModelSimple"); }

private:
	UPROPERTY() TObjectPtr<UAircraftConfigDataAsset> Config = nullptr;

	FVector LastForce_World = FVector::ZeroVector;
	FVector LastTorque_World = FVector::ZeroVector;

	static float AirDensityKgM3(float AltitudeMeters);
	float ComputeLift(float DynamicPressure, float AoARad) const;
	float ComputeDrag(float DynamicPressure, float CL) const;
	float ComputeThrustN(float ThrottleNorm, float AirDensity) const;
};
