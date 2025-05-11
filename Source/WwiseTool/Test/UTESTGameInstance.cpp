// Fill out your copyright notice in the Description page of Project Settings.


#include "UTESTGameInstance.h"

#include "TESTAudioSystem.h"
#include "TESTEventSubsystem.h"
#include "TESTHUDSystem.h"

class UTESTAudioSystem;
class UTESTHUDSystem;

void UUTESTGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("GameInstance Initialized."));

	// **强制初始化所有 EngineSubsystem**
	GEngine->GetEngineSubsystem<UTESTHUDSystem>()->InitializeEvent();
	GEngine->GetEngineSubsystem<UTESTAudioSystem>()->InitializeEvent();

	
}

void UUTESTGameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Log, TEXT("GameInstance Shutdown."));
}
