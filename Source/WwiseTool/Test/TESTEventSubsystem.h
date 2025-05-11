// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AudioEngineSubsystem.h"
#include "TESTEventSubsystem.generated.h"

/**
 * 
 */


// 事件委托
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEvent, FName);

UCLASS()
class WWISETOOL_API UTESTEventSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** 获取事件委托（仅供 `EventHelper` 使用） */
	static FOnGameEvent& GetEventDelegate();

private:
	static FOnGameEvent OnGameEvent;
};
