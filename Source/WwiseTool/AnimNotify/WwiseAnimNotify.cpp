// Fill out your copyright notice in the Description page of Project Settings.


#include "WwiseAnimNotify.h"

#include "AkGameplayStatics.h"
#include "WwiseTool/Struct/WwiseStrcut.h"

struct FWwiseDataTableSwitch;


void UWwiseAnimNotify::SetWwiseSwitchByPhysicalSurface(FName Name, AActor* Owner)
{
	if(DataTable == nullptr)
		return;
	FString ContentString = FString::Printf(TEXT("Content"));
	FWwiseDataTableSwitch* SwitchData = DataTable->FindRow<FWwiseDataTableSwitch>(Name, ContentString,false);

	if(SwitchData != nullptr)
	{
		UAkGameplayStatics::SetSwitch(SwitchData->SwitchValue,Owner);
	}
}
