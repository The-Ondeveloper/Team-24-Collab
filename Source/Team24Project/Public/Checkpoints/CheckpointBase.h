// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointBase.generated.h"

class UCollider;

UCLASS()
class TEAM24PROJECT_API ACheckpointBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpointBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	bool bTriggersOnlyOnce = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCollider> Collider;

	UFUNCTION(BlueprintNativeEvent, Category = "Checkpoint")
	void CheckpointActivated();
	
private:

	UFUNCTION()
	void OnColliderTrigger(AActor* OverlappedActor);
	
	bool bHasTriggered = false;
	
};
