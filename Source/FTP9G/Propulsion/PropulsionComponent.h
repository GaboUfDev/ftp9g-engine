// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PropulsionComponent.generated.h"

class UAircraftConfigDataAsset;

UCLASS(ClassGroup = (FTP9G), meta = (BlueprintSpawnableComponent))
class FTP9G_API UPropulsionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPropulsionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTP9G|Propulsion")
	TObjectPtr<UAircraftConfigDataAsset> AircraftConfig;

	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Propulsion") float CurrentRPM = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Propulsion") float CurrentPowerHP = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Propulsion") float FuelFlowLitersPerHour = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Propulsion") float OilTempC = 60.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Propulsion") float CHTempC = 80.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Propulsion") bool bRunning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTP9G|Propulsion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ThrottleInput = 0.0f;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "FTP9G|Propulsion")
	void StartEngine();

	UFUNCTION(BlueprintCallable, Category = "FTP9G|Propulsion")
	void ShutdownEngine();
};
