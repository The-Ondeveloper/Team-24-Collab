// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "ButtonBase.generated.h"

class UCollider;

UCLASS()
class TEAM24PROJECT_API AButtonBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AButtonBase();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCollider> Collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnButtonBeginOverlap(AActor* OverlappedActor);

	UFUNCTION()
	void OnButtonEndOverlap(AActor* OtherActor);
	
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
};
