// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoints/KillZone.h"

#include "GameModes/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AKillZone::AKillZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
}

void AKillZone::CheckpointActivated_Implementation(AActor* OverlappedActor)
{	
	if (bPlayerOnly)
	{
		if (OverlappedActor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(OverlappedActor, 10000, nullptr, this, nullptr);
		}
	}
	else
	{
		UGameplayStatics::ApplyDamage(OverlappedActor, 10000, nullptr, this, nullptr);
	}
	
	Super::CheckpointActivated_Implementation(OverlappedActor);
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

