// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckpointBase.h"
#include "PressurePlate.generated.h"

UCLASS()
class TEAM24PROJECT_API APressurePlate : public ACheckpointBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void CheckpointActivated_Implementation(AActor* OverlappedActor) override;
	virtual void CheckpointDeactivated_Implementation(AActor* OverlappedActor) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger Data")
	TArray<AActor*> TriggerTargets;

	UPROPERTY(BlueprintReadWrite, Category = "Trigger Data")
	bool bTriggered;

	
};
