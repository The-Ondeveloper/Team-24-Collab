// Fill out your copyright notice in the Description page of Project Settings.


#include "Team24Project/Public/GameModes/BaseGameMode.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


ABaseGameMode::ABaseGameMode()
{
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> StartArray;

	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), StartArray);

	PlayerStart = Cast<APlayerStart>(StartArray.Last());
	PlayerStart->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	
	SpawnLocation = PlayerStart->GetActorLocation();
	SpawnRotation = PlayerStart->GetActorRotation();
}

void ABaseGameMode::ChangeLevel_Implementation(const TSoftObjectPtr<UWorld>& NewLevel)
{
	if (bPrintDebugMessages)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Attempting to Load new level")));
	}

	LoadLevel(NewLevel);
}

void ABaseGameMode::RespawnPlayer()
{
	DestroyPlayer();
	
	HandleStartingNewPlayer(UGameplayStatics::GetPlayerController(this, 0));

	if (OnPlayerSpawn.IsBound())
	{
		OnPlayerSpawn.Broadcast();
	}
}

void ABaseGameMode::UpdatePlayerSpawn(FVector NewLocation, FRotator NewRotation)
{
	SpawnLocation = NewLocation;
	SpawnRotation = NewRotation;

	PlayerStart->SetActorLocation(SpawnLocation);
	PlayerStart->SetActorRotation(SpawnRotation);

	if (OnPlayerUpdateSpawn.IsBound())
	{
		OnPlayerUpdateSpawn.Broadcast(SpawnLocation, SpawnRotation);
	}
}

void ABaseGameMode::DestroyPlayer()
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(this, 0);

	player->Destroy();

	if (OnPlayerDeath.IsBound())
	{
		OnPlayerDeath.Broadcast();
	}
}

void ABaseGameMode::LoadLevel(TSoftObjectPtr<UWorld> NewLevel)
{
	FSoftObjectPath MapRef = NewLevel.ToSoftObjectPath();
	if (!MapRef.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("BaseGameMode: GameplayMapRef is invalid!"))
		return;
	}

	FString MapPath = MapRef.ToString();
	FName MapName = FName(*FPackageName::ObjectPathToPackageName(MapPath));
	UGameplayStatics::OpenLevel(this, MapName);

	if (OnChangeLevel.IsBound())
	{
		OnChangeLevel.Broadcast(NewLevel);
	}
}
