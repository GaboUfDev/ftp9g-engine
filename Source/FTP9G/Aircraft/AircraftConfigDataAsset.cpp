// Copyright FTP9G Project. All Rights Reserved.

#include "AircraftConfigDataAsset.h"
#include "FTP9G.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

bool UAircraftConfigDataAsset::LoadFromJsonFile(const FString& AbsolutePath)
{
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *AbsolutePath))
	{
		UE_LOG(LogFTP9G, Error, TEXT("AircraftConfig: cannot read file %s"), *AbsolutePath);
		return false;
	}
	return LoadFromJsonString(JsonString);
}

bool UAircraftConfigDataAsset::LoadFromJsonString(const FString& JsonString)
{
	const bool bOk = FJsonObjectConverter::JsonObjectStringToUStruct<UAircraftConfigDataAsset>(
		JsonString, this, 0, 0);
	if (!bOk)
	{
		UE_LOG(LogFTP9G, Error, TEXT("AircraftConfig: JSON parse failed"));
		return false;
	}
	UE_LOG(LogFTP9G, Log, TEXT("AircraftConfig loaded: %s"), *AircraftId);
	return true;
}
