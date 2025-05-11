// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WutheringWaveHUD.generated.h"

/**
 * 
 */

class UWutheringWaveRoleDataWidget;
static int32 MaxCharacterCount = 2;

UCLASS()
class WWISETOOL_API AWutheringWaveHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void InitHUD();
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetHUDInputMode(bool InputState);


#pragma region ControlCharacter

private:
	TObjectPtr<UWutheringWaveRoleDataWidget> CharacterWidget;
	int32 CharacterIndex = -1;

public:
	UFUNCTION(BlueprintCallable, Category = "HUD | Character")
	void ChangeCharacter(int32 Index);
	UFUNCTION(BlueprintCallable, Category = "HUD | Character")
	UWutheringWaveRoleDataWidget* GetCharacterWidget(int32& Index);
	UFUNCTION(BlueprintCallable, Category = "HUD | Character")
	void RefreshCharacter();

#pragma endregion

#pragma region Character Tarray

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "HUD | Character Array")
	TArray<TObjectPtr<UWutheringWaveRoleDataWidget>> CharacterWidgetArray;	// 3 roles

	UFUNCTION(BlueprintCallable, Category = "HUD | Character Array")
	void CharacterEntryArray(int32 Index,UWutheringWaveRoleDataWidget* Widget);
	UFUNCTION(BlueprintCallable, Category = "HUD | Character Array")
	void CharacterLeaveArray(int32 Index);
	
#pragma endregion
};
