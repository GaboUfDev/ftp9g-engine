// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AircraftConfigDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAircraftGeometry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float WingSpanMeters = 9.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float WingAreaSqMeters = 12.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float AspectRatio = 9.7f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MeanChordMeters = 1.27f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float FuselageLengthMeters = 7.2f;
};

USTRUCT(BlueprintType)
struct FAircraftMass
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float EmptyKg = 480.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxTakeoffKg = 750.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float FuelCapacityLiters = 120.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FVector CenterOfGravityMeters = FVector(0.0f, 0.0f, 0.0f);
};

USTRUCT(BlueprintType)
struct FAircraftAerodynamics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CL_Alpha = 5.7f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CL_Max = 1.4f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CL_0 = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CD_0 = 0.027f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float OswaldEfficiency = 0.80f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float StallAngleOfAttackDeg = 16.0f;
};

USTRUCT(BlueprintType)
struct FAircraftEngine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Model = TEXT("Rotax 915 iS");
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxPowerHP = 141.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxContinuousPowerHP = 135.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxRPM = 5800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float IdleRPM = 1800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float FuelFlowMaxLitersPerHour = 38.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bIsTurbocharged = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bHasFADEC = true;
};

USTRUCT(BlueprintType)
struct FAircraftPerformance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float StallSpeedClean_kts = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float StallSpeedFlaps_kts = 38.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float CruiseSpeed_kts = 130.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxSpeedVne_kts = 165.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float ServiceCeiling_ft = 18000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxClimbRate_fpm = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MaxLoadFactorG = 4.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float MinLoadFactorG = -2.0f;
};

UCLASS(BlueprintType)
class FTP9G_API UAircraftConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString AircraftId = TEXT("TP-150-RG");
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DisplayName = TEXT("TP-150 RG");
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Manufacturer = TEXT("FTP9G Reference");
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString DataSource = TEXT("public");

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FAircraftGeometry Geometry;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FAircraftMass Mass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FAircraftAerodynamics Aero;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FAircraftEngine Engine;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FAircraftPerformance Performance;

	UFUNCTION(BlueprintCallable, Category = "FTP9G|Aircraft")
	bool LoadFromJsonFile(const FString& AbsolutePath);

	UFUNCTION(BlueprintCallable, Category = "FTP9G|Aircraft")
	bool LoadFromJsonString(const FString& JsonString);
};
