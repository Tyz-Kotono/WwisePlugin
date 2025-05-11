// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AkAudioBank.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WwiseLibrary.generated.h"

class UAkAudioEvent;
class ULoudnessNRT;
class UConstantQNRT;
class UAkAudioEvent;
class FWaitEndBankAction;

/**
 * 
 */
UCLASS()
class WWISETOOL_API UWwiseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "WwiseLibrary")
	static int32 GetSourcePlayPosition(int32 AkPlayingID );

	UFUNCTION(BlueprintCallable, Category = "WwiseLibrary")
	static int32 GetSourcePlayPositionBySoundEngine(int32 PlayingID );


	/** UConstantQNRT
	 *
	 * UConstantQNRT calculates the temporal evolution of constant q transform for a given 
	 * sound. ConstantQ is available for individual channels or the overall sound asset.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Kotono/NRT")
	static void GetFrequencyByConstantQNRT(int32 PlayingID,const int32 InChannelIdx,UConstantQNRT* ConstantQNRT,TArray<float>& OutConstantQ);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "WwiseSubsystem | NRT ")
	static void GetFrequencyBandsFormConstantQNRT(int32 PlayingID, const int32 InChannel,UConstantQNRT* ConstantQNRT, float Multiple,TArray<float>& OutConstantQ ,
													   float& Bass,float& Medium,float& Hight );
	
	/** ULoudnessNRT
	 *
	 * ULoudnessNRT calculates the temporal evolution of perceptual loudness for a given 
	 * sound. Loudness is available for individual channels or the overall sound asset. Normalized 
	 * loudness values convert the range to 0.0 to 1.0 where 0.0 is the noise floor and 1.0 is the
	 * maximum loudness of the particular sound.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Kotono/NRT")
	static void GetFrequencyByLoudnessNRT(int32 PlayingID,const int32 InChannelIdx,ULoudnessNRT* LoudnessNRT,float& OutLoudness);


};
