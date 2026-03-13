// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoints/PressurePlate.h"

#include "Interfaces/Triggerable.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APressurePlate::APressurePlate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APressurePlate::CheckpointActivated_Implementation(AActor* OverlappedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Pressure plate activated")));

	bTriggered = true;
	
	if (TriggerTargets.Num() <= 0) return;

	for (auto target : TriggerTargets)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(target, UTriggerable::StaticClass()))
		{
			ITriggerable::Execute_OnTrigger(target);
		}
	}
	
	Super::CheckpointActivated_Implementation(OverlappedActor);
}

void APressurePlate::CheckpointDeactivated_Implementation(AActor* OverlappedActor)
{
	Super::CheckpointDeactivated_Implementation(OverlappedActor);

	bTriggered = false;
}

