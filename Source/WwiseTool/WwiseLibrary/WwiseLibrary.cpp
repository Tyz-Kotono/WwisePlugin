// Fill out your copyright notice in the Description page of Project Settings.


#include "WwiseLibrary.h"

#include <AK/SoundEngine/Common/AkTypes.h>
#include "AkAudioEvent.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>

#include "AkAudioDevice.h"
#include "Wwise/WwiseExternalSourceManager.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"


#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>   
#include "AkAudioEvent.h"
#include "AkGameplayStatics.h"
#include "Wwise/WwiseExternalSourceManager.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"
#include "ConstantQNRT.h"
#include "LoudnessNRT.h"



int32 UWwiseLibrary::GetSourcePlayPosition(int32 PlayingID)
{
	AkTimeMs Position = 0;
	auto* SoundEngine = IWwiseSoundEngineAPI::Get();
	auto Result = SoundEngine->GetSourcePlayPosition((AkPlayingID)PlayingID, &Position);
	// auto Result = AK::SoundEngine::GetSourcePlayPosition((AkPlayingID)PlayingID, &Position);
	if (Result != AKRESULT::AK_Success)
	{
		UE_LOG(LogScript, Warning, TEXT("UAkGameplayStatics::GetSourcePlayPosition: Failed"));
		return Result;
	}	
	else return (int32)Position;
}

int32 UWwiseLibrary::GetSourcePlayPositionBySoundEngine(int32 PlayingID)
{
	auto* AudioDevice = FAkAudioDevice::Get();
	if (UNLIKELY(!AudioDevice)|| UNLIKELY(!AudioDevice->IsInitialized()))
	{
		return AK_INVALID_PLAYING_ID;
	}
	
	auto* SoundEngine = IWwiseSoundEngineAPI::Get();
	if (UNLIKELY(!SoundEngine) || UNLIKELY(!SoundEngine->IsInitialized()))
	{
		return AK_INVALID_PLAYING_ID;
	}

	IWwiseExternalSourceManagerPtr ExternalSourceManager = IWwiseExternalSourceManager::Get();
	if (UNLIKELY(!ExternalSourceManager))
	{
		return AK_INVALID_PLAYING_ID;
	}

	AkTimeMs CurrentPosition = 0;
	auto Result = SoundEngine->GetSourcePlayPosition(PlayingID, &CurrentPosition);
	if (Result == AK_Success)
	{
		return CurrentPosition;
	}
	return Result;
}




void UWwiseLibrary::GetFrequencyByConstantQNRT(int32 PlayingID,const int32 InChannelIdx,UConstantQNRT* ConstantQNRT,TArray<float>& OutConstantQ)
{
	if(ConstantQNRT == nullptr || PlayingID == AK_INVALID_PLAYING_ID)
		return;
	const float InSeconds = GetSourcePlayPosition(PlayingID)/1000.0;
	ConstantQNRT->GetNormalizedChannelConstantQAtTime(InSeconds,InChannelIdx,OutConstantQ);
}

void UWwiseLibrary::GetFrequencyBandsFormConstantQNRT(int32 PlayingID, const int32 InChannel,
	UConstantQNRT* ConstantQNRT, float Multiple,TArray<float>& OutConstantQ, float& Bass, float& Medium, float& Hight)
{
	if(ConstantQNRT == nullptr || PlayingID == AK_INVALID_PLAYING_ID)
		return;

	const float TimePosition = GetSourcePlayPosition(PlayingID) / 1000.0f;
	ConstantQNRT->GetNormalizedChannelConstantQAtTime(TimePosition, InChannel, OutConstantQ);


	int Index =  OutConstantQ.Num() / 6 ;
	Bass = OutConstantQ[Index] * Multiple;
	Medium = OutConstantQ[Index * 3] * Multiple;
	Hight = OutConstantQ[Index * 5] * Multiple;
}



void UWwiseLibrary::GetFrequencyByLoudnessNRT(int32 PlayingID, const int32 InChannelIdx,ULoudnessNRT* LoudnessNRT, float& OutLoudness)
{
	if(LoudnessNRT == nullptr || PlayingID == AK_INVALID_PLAYING_ID)
		return;
	const float InSeconds = GetSourcePlayPosition(PlayingID)/1000.0;
	LoudnessNRT->GetNormalizedChannelLoudnessAtTime(InSeconds,InChannelIdx,OutLoudness);
}




