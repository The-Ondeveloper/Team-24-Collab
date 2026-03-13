// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointBase.generated.h"

class UCollider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckPointActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckPointDeactivated);

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

	UPROPERTY(EditInstanceOnly)
	bool bPlayerOnly = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCheckPointActivated OnCheckPointActivated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCheckPointDeactivated OnCheckPointDeactivated;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCollider> Collider;

	UFUNCTION(BlueprintNativeEvent, Category = "Checkpoint")
	void CheckpointActivated(AActor* OverlappedActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Checkpoint")
	void CheckpointDeactivated(AActor* OverlappedActor);
	
private:

	UFUNCTION()
	void OnColliderTrigger(AActor* OverlappedActor);
	
	bool bHasTriggered = false;
	
};
