// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "WwiseAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class WWISETOOL_API UWwiseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere)
	UDataTable* DataTable;

	UFUNCTION(BlueprintCallable,category="AnimNotify")
	void SetWwiseSwitchByPhysicalSurface(FName Name, AActor* Owner);
};
