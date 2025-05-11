// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTLibrary.h"


void UTESTLibrary::SubscribeEvent(const FOnGameEvent::FDelegate& Delegate)
{
	if (UTESTEventSubsystem* EventSubsystem = GEngine->GetEngineSubsystem<UTESTEventSubsystem>())
	{
		EventSubsystem->GetEventDelegate().Add(Delegate);
	}
}

void UTESTLibrary::SubscribeEvent_BP(const FGameEventBPDelegate& BPDelegate)
{
	if (UTESTEventSubsystem* EventSubsystem = GEngine->GetEngineSubsystem<UTESTEventSubsystem>())
	{
		// 转换蓝图委托到 C++ 委托
		EventSubsystem->GetEventDelegate().AddLambda([BPDelegate](FName EventName)
		{
			BPDelegate.ExecuteIfBound(EventName);
		});
	}
}

void UTESTLibrary::BroadcastEvent(FName EventName)
{
	if (UTESTEventSubsystem* EventSubsystem = GEngine->GetEngineSubsystem<UTESTEventSubsystem>())
	{
		EventSubsystem->GetEventDelegate().Broadcast(EventName);
	}
}

void UTESTLibrary::BroadcastEvent_BP(FName EventName)
{
	BroadcastEvent(EventName);
}