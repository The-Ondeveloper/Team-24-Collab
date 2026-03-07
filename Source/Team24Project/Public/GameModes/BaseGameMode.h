// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeLevel, TSoftObjectPtr<UWorld>, NewLevel);

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
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gamemode")
	void ChangeLevel(const TSoftObjectPtr<UWorld>& NewLevel);

private:
	
	UFUNCTION(BlueprintCallable, Category = "Gamemode")
	void LoadLevel(TSoftObjectPtr<UWorld> NewLevel);
};
