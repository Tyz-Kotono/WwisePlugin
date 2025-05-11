// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTEventSubsystem.h"
FOnGameEvent UTESTEventSubsystem::OnGameEvent;  // 在 .cpp 里定义静态变量

void UTESTEventSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("EventManagerSubsystem Initialized"));
}

void UTESTEventSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnGameEvent.Clear();
	UE_LOG(LogTemp, Log, TEXT("EventManagerSubsystem Deinitialized"));
}

FOnGameEvent& UTESTEventSubsystem::GetEventDelegate()
{
	return OnGameEvent;
}
