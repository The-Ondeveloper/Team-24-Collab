// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckpointBase.h"
#include "EndZone.generated.h"

UCLASS()
class TEAM24PROJECT_API AEndZone : public ACheckpointBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEndZone();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> LevelToLoad;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CheckpointActivated_Implementation(AActor* OverlappedActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
