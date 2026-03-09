// Fill out your copyright notice in the Description page of Project Settings.


#include "Team24Project/Public/Checkpoints/EndZone.h"

#include "Team24Project/Public/GameModes/BaseGameMode.h"


// Sets default values
AEndZone::AEndZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEndZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndZone::CheckpointActivated_Implementation(AActor* OverlappedActor)
{
	if (ABaseGameMode* Gamemode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Gamemode->ChangeLevel(LevelToLoad);
		UE_LOG(LogTemp, Warning, TEXT("Level changed"));
	}
	
	Super::CheckpointActivated_Implementation(OverlappedActor);
}

// Called every frame
void AEndZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

