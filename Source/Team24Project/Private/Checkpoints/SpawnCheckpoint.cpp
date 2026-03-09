// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoints/SpawnCheckpoint.h"

#include "GameFramework/Character.h"
#include "GameModes/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpawnCheckpoint::ASpawnCheckpoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnCheckpoint::CheckpointActivated_Implementation()
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(this, 0);
	FRotator playerRot = prevPlayerRot;

	if (player)
	{
		playerRot = player->GetActorRotation();
		prevPlayerRot = playerRot;
	}
	
	if (ABaseGameMode* Gamemode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Gamemode->UpdatePlayerSpawn(GetActorLocation(), playerRot);
		UE_LOG(LogTemp, Warning, TEXT("Updated Spawn"));
	}
	
	Super::CheckpointActivated_Implementation();
}

// Called every frame
void ASpawnCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

