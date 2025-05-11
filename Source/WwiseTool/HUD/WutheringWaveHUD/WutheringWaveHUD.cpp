// Fill out your copyright notice in the Description page of Project Settings.


#include "WutheringWaveHUD.h"

#include "RoleDataWidget/WutheringWaveRoleDataWidget.h"

void AWutheringWaveHUD::InitHUD()
{
	if(CharacterWidgetArray.IsEmpty())
	{
		return;
	}
	for (int32 Index = 0;Index < CharacterWidgetArray.Num();Index++)
	{
		if(CharacterWidgetArray[Index])
		{
			if(CharacterIndex <=0 && CharacterWidget == nullptr)
			{
				CharacterWidget = CharacterWidgetArray[Index];
				CharacterIndex = Index;

				CharacterWidgetArray[Index]->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				CharacterWidgetArray[Index]->SetVisibility(ESlateVisibility::Hidden);
			}
			CharacterWidgetArray[Index]->AddToViewport();
		}
	}
}

void AWutheringWaveHUD::SetHUDInputMode(bool InputState)
{
}

#pragma region ControlCharacter


UWutheringWaveRoleDataWidget* AWutheringWaveHUD::GetCharacterWidget(int32& Index)
{
	if(CharacterIndex <=0 && CharacterWidget == nullptr)
		return nullptr;
	Index = CharacterIndex;
	return CharacterWidget;
}

void AWutheringWaveHUD::ChangeCharacter(int32 Index)
{
	UWutheringWaveRoleDataWidget* Widget = CharacterWidgetArray[Index];
	if(Index > MaxCharacterCount || Index == CharacterIndex || Widget == nullptr)
	{
		return;
	}
	
	if(CharacterWidget == nullptr)
	{
		CharacterWidget = Widget;
	}
	else
	{
		CharacterWidget->SetVisibility(ESlateVisibility::Hidden);
		Widget->SetVisibility(ESlateVisibility::Visible);
		CharacterWidget = Widget;
	}
	
	CharacterIndex = Index;
}

void AWutheringWaveHUD::RefreshCharacter()
{
}

#pragma endregion

#pragma region Character Tarray

void AWutheringWaveHUD::CharacterEntryArray(int32 Index, UWutheringWaveRoleDataWidget* Widget)
{
	if(Widget)
	{
		CharacterWidgetArray[Index] = Widget;
	}
}

void AWutheringWaveHUD::CharacterLeaveArray(int32 Index)
{
	CharacterWidgetArray[Index] = nullptr;
}
#pragma endregion