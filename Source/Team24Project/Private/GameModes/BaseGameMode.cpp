// Fill out your copyright notice in the Description page of Project Settings.


#include "Team24Project/Public/GameModes/BaseGameMode.h"

#include "Kismet/GameplayStatics.h"


ABaseGameMode::ABaseGameMode()
{
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();


	
}

void ABaseGameMode::ChangeLevel_Implementation(const TSoftObjectPtr<UWorld>& NewLevel)
{
	if (bPrintDebugMessages)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Attempting to Load new level")));
	}

	LoadLevel(NewLevel);
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
