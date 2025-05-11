// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "WwiseStrcut.generated.h"

class UAkSwitchValue;

USTRUCT(BlueprintType)
struct FWwiseDataTableSwitch : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAkSwitchValue> SwitchValue;
};

UCLASS()
class WWISETOOL_API AWwiseStrcut : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWwiseStrcut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
