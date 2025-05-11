// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TESTLibrary.h"
#include "Subsystems/EngineSubsystem.h"
#include "TESTAudioSystem.generated.h"

/**
 * 
 */
UCLASS()
class WWISETOOL_API UTESTAudioSystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
	}

	void InitializeEvent()
	{
		UE_LOG(LogTemp, Log, TEXT("Audio System Initialize."));
		// 使用静态工具类订阅事件
		UTESTLibrary::SubscribeEvent(FOnGameEvent::FDelegate::CreateUObject(this, &UTESTAudioSystem::HandleEvent));
	}

	virtual void Deinitialize() override
	{
		Super::Deinitialize();
	}

	void HandleEvent(FName EventName)
	{
		UE_LOG(LogTemp, Log, TEXT("Audio System received event."));
	}
};
