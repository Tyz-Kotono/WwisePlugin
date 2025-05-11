// Fill out your copyright notice in the Description page of Project Settings.


#include "WutheringWaveRoleDataWidget.h"
#include "../WutheringWaveSingleFrequencyWidget.h"
#include "Components/WrapBox.h"

void UWutheringWaveRoleDataWidget::RoleEnter_Implementation()
{
}

void UWutheringWaveRoleDataWidget::RoleLeave_Implementation()
{
}

void UWutheringWaveRoleDataWidget::AddSingleFrequencyWidget(UWutheringWaveSingleFrequencyWidget* Widget, UWrapBox* Warp)
{
	if(Widget == nullptr || Warp == nullptr)
		return;
	WWFrequebcyArray.Add(Widget);
	Warp->AddChild(Widget);
	
}

void UWutheringWaveRoleDataWidget::SetSingleFrequency(TArray<float> Percent)
{
	if(WWFrequebcyArray.IsEmpty() || Percent.IsEmpty())
		return;
	for(int i = 0; i < WWFrequebcyArray.Num(); i++)
	{
		if(i>Percent.Num())
			return;
		WWFrequebcyArray[i]->SetFrequency(Percent[i]);
	}
}

void UWutheringWaveRoleDataWidget::RemoveSingleWidget(int32 Index, UWrapBox* Warp)
{
	if(!WWFrequebcyArray.IsValidIndex(Index)|| Warp == nullptr)
		return;
	if(Warp->GetChildrenCount() <=Index)
		return;

	WWFrequebcyArray.RemoveAt(Index);
	Warp->RemoveChildAt(Index);
}
