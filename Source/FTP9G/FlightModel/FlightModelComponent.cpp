// Copyright FTP9G Project. All Rights Reserved.

#include "FlightModelComponent.h"
#include "FlightModelSimple.h"
#include "Aircraft/AircraftConfigDataAsset.h"
#include "FTP9G.h"

UFlightModelComponent::UFlightModelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFlightModelComponent::BeginPlay()
{
	Super::BeginPlay();
	RebuildModel();
}

void UFlightModelComponent::RebuildModel()
{
	UObject* NewObj = nullptr;
	switch (ModelType)
	{
		case EFlightModelType::Simple:
			NewObj = NewObject<UFlightModelSimple>(this);
			break;
		case EFlightModelType::RealisticPiston:
		case EFlightModelType::Jet:
			UE_LOG(LogFTP9G, Warning, TEXT("FlightModel type not yet implemented; falling back to Simple."));
			NewObj = NewObject<UFlightModelSimple>(this);
			break;
	}

	ActiveModel.SetObject(NewObj);
	ActiveModel.SetInterface(Cast<IFlightModel>(NewObj));

	if (IFlightModel* Iface = Cast<IFlightModel>(NewObj))
	{
		Iface->Initialize(AircraftConfig);
	}
}

void UFlightModelComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IFlightModel* Iface = Cast<IFlightModel>(ActiveModel.GetObject()))
	{
		Iface->Step(DeltaTime, Inputs, State);
	}
}
