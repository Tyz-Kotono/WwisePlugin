// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <AK/SoundEngine/Common/AkTypes.h>

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "WwiseSubsystem.generated.h"

class ULoudnessNRT;
class UConstantQNRT;
/**
 * 
 */
UCLASS()
class WWISETOOL_API UWwiseSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	AkPlayingID CurrentPlayingID,PrePlayingID;
	TObjectPtr<UConstantQNRT> CurrentQNRT,PreQNRT;
	TObjectPtr<ULoudnessNRT> CurrentLNRT,PreLNRT;
	
public:
	bool IsInitialized = false;
	UFUNCTION(BlueprintCallable)
	void WwiseInitialized() ;

	//Set Wwise Data
	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | WWise ")
	void SetCurrentPlayingID(int32 AkPlayingID, bool CurrentID = true) ;

	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | WWise ")
	void SetCurrentConstantQNRT(UConstantQNRT* ConstantQNRT, bool CurrentNRT = true) ;

	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | WWise ")
	void SetCurrentLoudnessNRT(ULoudnessNRT* LoudnessNRT, bool CurrentNRT = true) ;

	//Get Data
	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | WWise ")
	int32 GetCurrentPlayingID(bool CurrentID = true) ;

	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | WWise ")
	UConstantQNRT* GetCurrentConstantQNRT(bool CurrentNRT = true) ;

	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | WWise ")
	ULoudnessNRT* GetCurrentLoudnessNRT(bool CurrentNRT = true) ;

	
	//NRT
	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | NRT ")
	void GetFrequencyFormCurrentConstantQNRT(const int32 InChannel, TArray<float>& OutConstantQ);
	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category = "WwiseSubsystem | NRT ")
	void GetVolumeFormCurrentLoudnessNRT(const int32 InChannel, float& OutLoudness);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "WwiseSubsystem | NRT ")
	void GetFrequencyBandsFormCurrentConstantQNRT(const int32 InChannel, float Multiple ,
	                                                   float& Bass,float& Medium,float& Hight );
	 

};
