// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WutheringWaveRoleDataWidget.generated.h"

class UWrapBox;
class UProgressBar;
class UWutheringWaveSingleFrequencyWidget;
/**
 * 
 */
UCLASS()
class WWISETOOL_API UWutheringWaveRoleDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Frequency")
	TArray<TObjectPtr<UWutheringWaveSingleFrequencyWidget>> WWFrequebcyArray;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Frequency")
	int32 FrequencyBand = 48;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Role")
	TObjectPtr<UProgressBar> RolePro;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Category = "Role")
	void RoleEnter();
	virtual void RoleEnter_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable ,Category = "Role")
	void RoleLeave();
	virtual void RoleLeave_Implementation();
	
#pragma region Frequency

	UFUNCTION(BlueprintCallable,CallInEditor)
	void AddSingleFrequencyWidget(UWutheringWaveSingleFrequencyWidget* Widget,UWrapBox* Warp);

	UFUNCTION(BlueprintCallable,CallInEditor)
	void SetSingleFrequency(TArray<float> Percent);

	UFUNCTION(BlueprintCallable,CallInEditor)
	void RemoveSingleWidget(int32 Index,UWrapBox* Warp);
	
#pragma endregion
	
};
