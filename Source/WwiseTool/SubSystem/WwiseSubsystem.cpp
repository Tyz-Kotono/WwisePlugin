// Fill out your copyright notice in the Description page of Project Settings.


#include "WwiseSubsystem.h"

#include "ConstantQNRT.h"
#include "LoudnessNRT.h"
#include "Platforms/AkPlatform_Android/AkAndroidInitializationSettings.h"
#include "Wwise/WwiseFileHandlerModule.h"
#include "AK/Tools/Win32/AkPlatformFuncs.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"
#include "Wwise/WwiseIOHook.h"
#include "../WwiseLibrary/WwiseLibrary.h"

void UWwiseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWwiseSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UWwiseSubsystem::WwiseInitialized()
{
	if (IsInitialized)
		return;

	//Init AK Menory Manager
	//https://www.audiokinetic.com/zh/library/edge/?source=SDK&id=memorymanager.html
	AkMemSettings MenSetting;
	AK::MemoryMgr::GetDefaultSettings(MenSetting);
	AK::MemoryMgr::Init(&MenSetting);

	//Init Ak Stream Manager
	//https://www.audiokinetic.com/zh/library/edge/?source=SDK&id=streamingmanager_settings.html
	AkStreamMgrSettings StreamSetting;
	AK::StreamMgr::GetDefaultSettings(StreamSetting);
	AK::StreamMgr::Create(StreamSetting);

	//Init Sound Engine
	//https://www.audiokinetic.com/zh/library/edge/?source=SDK&id=namespace_a_k_1_1_stream_mgr_af9d67dd0e502e5603a2921099916e2ab.html#af9d67dd0e502e5603a2921099916e2ab
	AkInitSettings InitSettings;
	AkPlatformInitSettings PlatformInitSettings;

	//Init AK Device
	AkDeviceSettings DeviceSettings;

	//创建默认Device设置对象

	//I/O 内存大小
	DeviceSettings.pIOMemory = NULL;
	DeviceSettings.uIOMemorySize = 2;
	DeviceSettings.uIOMemoryAlignment = 4;
	// DeviceSettings.ePoolAttributes = AkMalloc;

	//粒度
	DeviceSettings.uGranularity = 16 * 1024;

	//IO
	AkThreadProperties out_threadProperties;
	AKPLATFORM::AkGetDefaultThreadProperties(out_threadProperties);
	DeviceSettings.threadProperties = out_threadProperties;

	//目标缓冲长度 defulat = 380 ms
	DeviceSettings.fTargetAutoStmBufferLength = 380;

	//并行 I/O 传输的最大数量
	DeviceSettings.uMaxConcurrentIO = 8;

	// 使用流缓存
	DeviceSettings.bUseStreamCache = false;

	AK::StreamMgr::GetDefaultDeviceSettings(DeviceSettings);

	auto* FileHandlerModule = IWwiseFileHandlerModule::GetModule();
	FWwiseIOHook* IOHook = FileHandlerModule->InstantiateIOHook();
	AkDeviceID idDevice;
	AK::StreamMgr::CreateDevice(DeviceSettings, IOHook->GetIOHook(), idDevice);


	// 配置初始化设置
	InitSettings.uMaxNumPaths = 4 * 4; // 设置线程栈大小等
	AK::SoundEngine::GetDefaultInitSettings(InitSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(PlatformInitSettings);
	AKRESULT Result = AK::SoundEngine::Init(&InitSettings, &PlatformInitSettings);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
	                                 FString::Printf(TEXT("WwiseSubsystem::WwiseInitialized %d"), Result));

	//https://www.audiokinetic.com/zh/library/edge/?source=SDK&id=workingwithsdks_initialization.html
	AkSpatialAudioInitSettings SpatialAudiosettings; // 构造函数将建议的默认设置赋予 AkSpatialAudioInitSettings。
	AK::SpatialAudio::Init(SpatialAudiosettings);


	IsInitialized = true;
}



void UWwiseSubsystem::SetCurrentPlayingID(int32 PlayingID, bool CurrentID)
{
	if (CurrentID)
		CurrentPlayingID = (AkPlayingID)PlayingID;
	else
		PrePlayingID = (AkPlayingID)PlayingID;
}

void UWwiseSubsystem::SetCurrentConstantQNRT(UConstantQNRT* ConstantQNRT, bool CurrentNRT)
{
	if (CurrentNRT)
		CurrentQNRT = ConstantQNRT;
	else
		PreQNRT = ConstantQNRT;
}

void UWwiseSubsystem::SetCurrentLoudnessNRT(ULoudnessNRT* LoudnessNRT, bool CurrentNRT)
{
	if (CurrentNRT)
		CurrentLNRT = LoudnessNRT;
	else
		PreLNRT = LoudnessNRT;
}

int32 UWwiseSubsystem::GetCurrentPlayingID(bool CurrentID)
{
	return CurrentID ? CurrentPlayingID : PrePlayingID;
}

UConstantQNRT* UWwiseSubsystem::GetCurrentConstantQNRT(bool CurrentNRT)
{
	return CurrentNRT ? CurrentQNRT : PreQNRT;
}

ULoudnessNRT* UWwiseSubsystem::GetCurrentLoudnessNRT(bool CurrentNRT)
{
	return CurrentNRT ? CurrentLNRT : PreLNRT;
}


void UWwiseSubsystem::GetFrequencyFormCurrentConstantQNRT(const int32 InChannel, TArray<float>& OutConstantQ)
{
	if (CurrentQNRT == nullptr)
		return;
	const float TimePosition = UWwiseLibrary::GetSourcePlayPosition(CurrentPlayingID) / 1000.0f;
	CurrentQNRT->GetNormalizedChannelConstantQAtTime(TimePosition, InChannel, OutConstantQ);
}

void UWwiseSubsystem::GetVolumeFormCurrentLoudnessNRT(const int32 InChannel, float& OutLoudness)
{
	if (CurrentLNRT == nullptr)
		return;
	const float TimePosition = UWwiseLibrary::GetSourcePlayPosition(CurrentPlayingID) / 1000.0f;
	CurrentLNRT->GetNormalizedChannelLoudnessAtTime(TimePosition, InChannel, OutLoudness);
}

void UWwiseSubsystem::GetFrequencyBandsFormCurrentConstantQNRT(const int32 InChannel, float Multiple, float& Bass, float& Medium,
	float& Hight)
{
	if (CurrentQNRT == nullptr)
		return;
	TArray<float> OutConstantQ;
	const float TimePosition = UWwiseLibrary::GetSourcePlayPosition(CurrentPlayingID) / 1000.0f;
	CurrentQNRT->GetNormalizedChannelConstantQAtTime(TimePosition, InChannel, OutConstantQ);


	int Index =  OutConstantQ.Num() / 6 ;
	Bass = OutConstantQ[Index] * Multiple;
	Medium = OutConstantQ[Index * 3] * Multiple;
	Hight = OutConstantQ[Index * 5] * Multiple;
}




