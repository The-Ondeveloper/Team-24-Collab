// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Triggerable.h"
#include "DoorBase.generated.h"

UCLASS()
class TEAM24PROJECT_API ADoorBase : public AActor, public ITriggerable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnTrigger_Implementation() override;
};
