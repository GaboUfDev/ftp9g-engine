// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlightModel.h"
#include "FlightModelComponent.generated.h"

class UAircraftConfigDataAsset;

UENUM(BlueprintType)
enum class EFlightModelType : uint8
{
	Simple UMETA(DisplayName = "Simple (Phase 0)"),
	RealisticPiston UMETA(DisplayName = "Realistic Piston (Phase 10)"),
	Jet UMETA(DisplayName = "Jet (Phase 14)")
};

UCLASS(ClassGroup = (FTP9G), meta = (BlueprintSpawnableComponent))
class FTP9G_API UFlightModelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFlightModelComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTP9G|FlightModel")
	EFlightModelType ModelType = EFlightModelType::Simple;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTP9G|FlightModel")
	TObjectPtr<UAircraftConfigDataAsset> AircraftConfig;

	UPROPERTY(BlueprintReadOnly, Category = "FTP9G|FlightModel")
	FFlightState State;

	UPROPERTY(BlueprintReadWrite, Category = "FTP9G|FlightModel")
	FFlightInputs Inputs;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "FTP9G|FlightModel")
	void RebuildModel();

private:
	UPROPERTY() TScriptInterface<IFlightModel> ActiveModel;
};
