// Copyright FTP9G Project. All Rights Reserved.

#include "FlightControlComponent.h"

UFlightControlComponent::UFlightControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFlightControlComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	constexpr float MaxAileronDeg = 20.0f;
	constexpr float MaxElevatorDeg = 25.0f;
	constexpr float MaxRudderDeg = 25.0f;
	constexpr float MaxFlapsDeg = 30.0f;

	AileronDeflectionDeg = FMath::FInterpTo(AileronDeflectionDeg, AileronInput * MaxAileronDeg, DeltaTime, ControlResponseRate);
	ElevatorDeflectionDeg = FMath::FInterpTo(ElevatorDeflectionDeg, ElevatorInput * MaxElevatorDeg, DeltaTime, ControlResponseRate);
	RudderDeflectionDeg = FMath::FInterpTo(RudderDeflectionDeg, RudderInput * MaxRudderDeg, DeltaTime, ControlResponseRate);
	FlapsDeflectionDeg = FMath::FInterpTo(FlapsDeflectionDeg, FlapsInput * MaxFlapsDeg, DeltaTime, 1.0f);
}
