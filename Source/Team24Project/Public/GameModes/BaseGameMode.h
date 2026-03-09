// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeLevel, TSoftObjectPtr<UWorld>, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerSpawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerUpdateSpawn, FVector, NewSpawnLocation, FRotator, NewSpawnRotation);

UCLASS()
class TEAM24PROJECT_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABaseGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	bool bPrintDebugMessages = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnChangeLevel OnChangeLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnPlayerSpawn OnPlayerSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnPlayerDeath OnPlayerDeath;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnPlayerUpdateSpawn OnPlayerUpdateSpawn;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gamemode")
	void ChangeLevel(const TSoftObjectPtr<UWorld>& NewLevel);

	UFUNCTION(BlueprintCallable, Category = "Gamemode")
	void RespawnPlayer();

	UFUNCTION(BlueprintCallable, Category = "Gamemode")
	void UpdatePlayerSpawn(FVector NewLocation, FRotator NewRotation);

	UFUNCTION(BlueprintCallable, Category = "Gamemode")
	void DestroyPlayer();
	
private:
	
	UFUNCTION(BlueprintCallable, Category = "Gamemode")
	void LoadLevel(TSoftObjectPtr<UWorld> NewLevel);

	UPROPERTY()
	APlayerStart* PlayerStart;
	
protected:

	UPROPERTY(BlueprintReadOnly)
	FVector SpawnLocation;

	UPROPERTY(BlueprintReadOnly)
	FRotator SpawnRotation;
};
