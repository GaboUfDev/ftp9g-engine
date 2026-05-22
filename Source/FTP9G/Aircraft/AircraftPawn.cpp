// Copyright FTP9G Project. All Rights Reserved.

#include "AircraftPawn.h"
#include "AircraftConfigDataAsset.h"
#include "FlightModel/FlightModelComponent.h"
#include "Propulsion/PropulsionComponent.h"
#include "FlightControl/FlightControlComponent.h"
#include "FTP9G.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

AAircraftPawn::AAircraftPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	HullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullMesh"));
	RootComponent = HullMesh;
	HullMesh->SetSimulatePhysics(true);
	HullMesh->SetEnableGravity(true);
	HullMesh->SetLinearDamping(0.1f);
	HullMesh->SetAngularDamping(2.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(HullMesh);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = false;

	CockpitCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CockpitCamera"));
	CockpitCamera->SetupAttachment(CameraBoom);

	FlightModel = CreateDefaultSubobject<UFlightModelComponent>(TEXT("FlightModel"));
	Propulsion = CreateDefaultSubobject<UPropulsionComponent>(TEXT("Propulsion"));
	Controls = CreateDefaultSubobject<UFlightControlComponent>(TEXT("Controls"));
}

void AAircraftPawn::BeginPlay()
{
	Super::BeginPlay();

	if (AircraftConfig)
	{
		FlightModel->AircraftConfig = AircraftConfig;
		Propulsion->AircraftConfig = AircraftConfig;
		FlightModel->RebuildModel();
		Propulsion->StartEngine();

		if (UStaticMeshComponent* Mesh = HullMesh)
		{
			Mesh->SetMassOverrideInKg(NAME_None, AircraftConfig->Mass.MaxTakeoffKg, true);
		}
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Sub =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (InputMapping) Sub->AddMappingContext(InputMapping, 0);
		}
	}
}

void AAircraftPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (FlightModel && Controls && Propulsion)
	{
		FlightModel->Inputs.Aileron = Controls->AileronInput;
		FlightModel->Inputs.Elevator = Controls->ElevatorInput;
		FlightModel->Inputs.Rudder = Controls->RudderInput;
		FlightModel->Inputs.Flaps = Controls->FlapsInput;
		FlightModel->Inputs.Brakes = Controls->BrakesInput;
		FlightModel->Inputs.bGearDown = Controls->bGearDown;
		FlightModel->Inputs.Throttle = Propulsion->ThrottleInput;
	}

	ApplyPhysicsFromFlightModel(DeltaSeconds);
}

void AAircraftPawn::ApplyPhysicsFromFlightModel(float DeltaSeconds)
{
	if (!FlightModel || !HullMesh) return;
	const IFlightModel* Model = nullptr;
	HullMesh->AddForce(FlightModel->State.WorldAcceleration * HullMesh->GetMass());
}

void AAircraftPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Pitch) EIC->BindAction(IA_Pitch, ETriggerEvent::Triggered, this, &AAircraftPawn::OnPitch);
		if (IA_Roll) EIC->BindAction(IA_Roll, ETriggerEvent::Triggered, this, &AAircraftPawn::OnRoll);
		if (IA_Yaw) EIC->BindAction(IA_Yaw, ETriggerEvent::Triggered, this, &AAircraftPawn::OnYaw);
		if (IA_Throttle) EIC->BindAction(IA_Throttle, ETriggerEvent::Triggered, this, &AAircraftPawn::OnThrottle);
		if (IA_Flaps) EIC->BindAction(IA_Flaps, ETriggerEvent::Triggered, this, &AAircraftPawn::OnFlaps);
		if (IA_Brakes) EIC->BindAction(IA_Brakes, ETriggerEvent::Triggered, this, &AAircraftPawn::OnBrakes);
		if (IA_Gear) EIC->BindAction(IA_Gear, ETriggerEvent::Started, this, &AAircraftPawn::OnToggleGear);
	}
}

void AAircraftPawn::OnPitch(const FInputActionValue& V) { if (Controls) Controls->ElevatorInput = FMath::Clamp(V.Get<float>(), -1.0f, 1.0f); }
void AAircraftPawn::OnRoll(const FInputActionValue& V) { if (Controls) Controls->AileronInput = FMath::Clamp(V.Get<float>(), -1.0f, 1.0f); }
void AAircraftPawn::OnYaw(const FInputActionValue& V) { if (Controls) Controls->RudderInput = FMath::Clamp(V.Get<float>(), -1.0f, 1.0f); }
void AAircraftPawn::OnThrottle(const FInputActionValue& V) { if (Propulsion) Propulsion->ThrottleInput = FMath::Clamp(V.Get<float>(), 0.0f, 1.0f); }
void AAircraftPawn::OnFlaps(const FInputActionValue& V) { if (Controls) Controls->FlapsInput = FMath::Clamp(V.Get<float>(), 0.0f, 1.0f); }
void AAircraftPawn::OnBrakes(const FInputActionValue& V) { if (Controls) Controls->BrakesInput = FMath::Clamp(V.Get<float>(), 0.0f, 1.0f); }
void AAircraftPawn::OnToggleGear(const FInputActionValue&) { if (Controls) Controls->bGearDown = !Controls->bGearDown; }
