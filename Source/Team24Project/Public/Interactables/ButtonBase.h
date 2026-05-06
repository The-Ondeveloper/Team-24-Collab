// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "ButtonBase.generated.h"

class UCollider;

UCLASS()
class TEAM24PROJECT_API AButtonBase : public ABaseInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AButtonBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	UPROPERTY(EditInstanceOnly, Category = "Trigger Data")
	TArray<AActor*> TriggerTargets;

	UPROPERTY(EditInstanceOnly, Category = "Trigger Data")
	bool bToggleTriggers = false;

	UPROPERTY(EditInstanceOnly, Category = "Trigger Data")
	bool bStartTriggered = false;

	UPROPERTY(EditDefaultsOnly, Category = "Sound Data")
	TObjectPtr<USoundBase> TriggerSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound Data")
	TObjectPtr<USoundBase> UnTriggerSound;


};
