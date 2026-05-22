// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FlightModel.generated.h"

class UAircraftConfigDataAsset;

USTRUCT(BlueprintType)
struct FFlightState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) FVector WorldVelocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite) FVector WorldAcceleration = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite) FRotator Attitude = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadWrite) FVector AngularVelocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite) float AirspeedKts = 0.0f;
	UPROPERTY(BlueprintReadWrite) float AltitudeFeet = 0.0f;
	UPROPERTY(BlueprintReadWrite) float AngleOfAttackDeg = 0.0f;
	UPROPERTY(BlueprintReadWrite) float SideslipDeg = 0.0f;
	UPROPERTY(BlueprintReadWrite) float LoadFactorG = 1.0f;
	UPROPERTY(BlueprintReadWrite) bool bStalled = false;
};

USTRUCT(BlueprintType)
struct FFlightInputs
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) float Aileron = 0.0f;
	UPROPERTY(BlueprintReadWrite) float Elevator = 0.0f;
	UPROPERTY(BlueprintReadWrite) float Rudder = 0.0f;
	UPROPERTY(BlueprintReadWrite) float Throttle = 0.0f;
	UPROPERTY(BlueprintReadWrite) float Flaps = 0.0f;
	UPROPERTY(BlueprintReadWrite) float Brakes = 0.0f;
	UPROPERTY(BlueprintReadWrite) bool bGearDown = true;
};

UINTERFACE(BlueprintType, MinimalAPI)
class UFlightModel : public UInterface
{
	GENERATED_BODY()
};

class FTP9G_API IFlightModel
{
	GENERATED_BODY()

public:
	virtual void Initialize(UAircraftConfigDataAsset* Config) = 0;
	virtual void Step(float DeltaSeconds, const FFlightInputs& Inputs, FFlightState& InOutState) = 0;
	virtual FVector GetLastAeroForce_World() const = 0;
	virtual FVector GetLastAeroTorque_World() const = 0;
	virtual FString GetModelName() const = 0;
};
