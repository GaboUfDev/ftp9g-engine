// Copyright FTP9G Project. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AircraftPawn.generated.h"

class UAircraftConfigDataAsset;
class UFlightModelComponent;
class UPropulsionComponent;
class UFlightControlComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS(Blueprintable, BlueprintType)
class FTP9G_API AAircraftPawn : public APawn
{
	GENERATED_BODY()

public:
	AAircraftPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FTP9G|Aircraft")
	TObjectPtr<UAircraftConfigDataAsset> AircraftConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> HullMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UCameraComponent> CockpitCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UFlightModelComponent> FlightModel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UPropulsionComponent> Propulsion;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UFlightControlComponent> Controls;

	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Pitch;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Roll;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Yaw;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Throttle;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Flaps;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Brakes;
	UPROPERTY(EditDefaultsOnly, Category = "FTP9G|Input") TObjectPtr<UInputAction> IA_Gear;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void OnPitch(const FInputActionValue& V);
	void OnRoll(const FInputActionValue& V);
	void OnYaw(const FInputActionValue& V);
	void OnThrottle(const FInputActionValue& V);
	void OnFlaps(const FInputActionValue& V);
	void OnBrakes(const FInputActionValue& V);
	void OnToggleGear(const FInputActionValue& V);

	void ApplyPhysicsFromFlightModel(float DeltaSeconds);
};
