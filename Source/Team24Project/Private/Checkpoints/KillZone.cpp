// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoints/KillZone.h"

#include "GameModes/BaseGameMode.h"


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

void AKillZone::CheckpointActivated_Implementation()
{
	if (ABaseGameMode* Gamemode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Gamemode->RespawnPlayer();
		UE_LOG(LogTemp, Warning, TEXT("KilledPlayer"));
	}
	
	Super::CheckpointActivated_Implementation();
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

