// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Triggerable.h"
#include "BaseMovingPlatform.generated.h"

USTRUCT(BlueprintType)
struct FPlatformTargetPoint
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TObjectPtr<ATargetPoint> Target;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float WaitTime = 0.f;
};

UCLASS()
class TEAM24PROJECT_API ABaseMovingPlatform : public AActor, public ITriggerable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	int CurrentTargetIndex = 0;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATargetPoint> CurrentTarget;

	UPROPERTY(BlueprintReadWrite)
	float WaitTimer = 0.f;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<FPlatformTargetPoint> TargetPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bTriggered;
	
	virtual void OnTrigger_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleMoving();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveToTarget(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetNewTarget();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float MoveSpeed = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bSmoothMovement = true;

	UPROPERTY(EditinstanceOnly, BlueprintReadWrite)
	float TargetDistance = 10.0f;

private:
	float MoveAlpha = 0.f;
	FVector StartLocation;
	bool bIsMoving = false;
};
