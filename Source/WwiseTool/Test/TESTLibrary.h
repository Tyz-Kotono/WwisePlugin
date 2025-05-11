// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TESTEventSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TESTLibrary.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_OneParam(FGameEventBPDelegate, FName, EventName);

UCLASS()
class WWISETOOL_API UTESTLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** C++ 订阅事件 */
	static void SubscribeEvent(const FOnGameEvent::FDelegate& Delegate);

	/** 蓝图订阅事件 */
	UFUNCTION(BlueprintCallable, Category = "Event System")
	static void SubscribeEvent_BP(const FGameEventBPDelegate& BPDelegate);

	/** C++ 触发事件 */
	static void BroadcastEvent(FName EventName);

	/** 蓝图触发事件 */
	UFUNCTION(BlueprintCallable, Category = "Event System")
	static void BroadcastEvent_BP(FName EventName);
};
