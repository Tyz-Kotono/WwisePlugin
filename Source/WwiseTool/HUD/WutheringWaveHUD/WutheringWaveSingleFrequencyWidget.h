// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WutheringWaveSingleFrequencyWidget.generated.h"

class USizeBox;
class UProgressBar;
/**
 * 
 */
UCLASS()
class WWISETOOL_API UWutheringWaveSingleFrequencyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget="true"))
	TObjectPtr<UProgressBar> FrequencyPro;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget="true"))
	TObjectPtr<USizeBox> FrequencySizeBox;

	UFUNCTION(BlueprintCallable)
	void SetFrequency(float Frequency);
};
