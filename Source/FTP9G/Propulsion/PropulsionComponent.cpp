// Copyright FTP9G Project. All Rights Reserved.

#include "PropulsionComponent.h"
#include "Aircraft/AircraftConfigDataAsset.h"
#include "FTP9G.h"

UPropulsionComponent::UPropulsionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPropulsionComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentRPM = 0.0f;
	bRunning = false;
}

void UPropulsionComponent::StartEngine()
{
	if (!AircraftConfig) return;
	bRunning = true;
	CurrentRPM = AircraftConfig->Engine.IdleRPM;
	UE_LOG(LogFTP9G, Log, TEXT("Engine started: %s"), *AircraftConfig->Engine.Model);
}

void UPropulsionComponent::ShutdownEngine()
{
	bRunning = false;
}

void UPropulsionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!AircraftConfig) return;

	const float MaxRPM = AircraftConfig->Engine.MaxRPM;
	const float IdleRPM = AircraftConfig->Engine.IdleRPM;
	const float TargetRPM = bRunning
		? FMath::Lerp(IdleRPM, MaxRPM, FMath::Clamp(ThrottleInput, 0.0f, 1.0f))
		: 0.0f;

	CurrentRPM = FMath::FInterpTo(CurrentRPM, TargetRPM, DeltaTime, 2.0f);
	CurrentPowerHP = AircraftConfig->Engine.MaxPowerHP * (CurrentRPM / MaxRPM);
	FuelFlowLitersPerHour = AircraftConfig->Engine.FuelFlowMaxLitersPerHour * (CurrentRPM / MaxRPM);
}
