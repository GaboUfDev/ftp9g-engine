// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlightControlComponent.generated.h"

UCLASS(ClassGroup = (FTP9G), meta = (BlueprintSpawnableComponent))
class FTP9G_API UFlightControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFlightControlComponent();

	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|Controls", meta = (ClampMin = "-1.0", ClampMax = "1.0")) float AileronInput = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|Controls", meta = (ClampMin = "-1.0", ClampMax = "1.0")) float ElevatorInput = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|Controls", meta = (ClampMin = "-1.0", ClampMax = "1.0")) float RudderInput = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|Controls", meta = (ClampMin = "0.0", ClampMax = "1.0")) float FlapsInput = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|Controls", meta = (ClampMin = "0.0", ClampMax = "1.0")) float BrakesInput = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|Controls") bool bGearDown = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTP9G|Controls")
	float ControlResponseRate = 4.0f;

	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Controls") float AileronDeflectionDeg = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Controls") float ElevatorDeflectionDeg = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Controls") float RudderDeflectionDeg = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|Controls") float FlapsDeflectionDeg = 0.0f;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
};
