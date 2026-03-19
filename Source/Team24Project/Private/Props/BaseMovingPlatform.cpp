// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/BaseMovingPlatform.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABaseMovingPlatform::ABaseMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if (TargetPoints.Num() > 0)
	{
		CurrentTargetIndex = 0;
		CurrentTarget = TargetPoints[CurrentTargetIndex].Target;
		WaitTimer = TargetPoints[CurrentTargetIndex].WaitTime;
	}
}

// Called every frame
void ABaseMovingPlatform::Tick(float DeltaTime)
{
	/*if (TargetPoints.Num() == 0) return;
	if (!TargetPoints.IsValidIndex(CurrentTargetIndex)) return;
	if (!IsValid(CurrentTarget)) return;

	if (WaitTimer > 0.f)
	{
		WaitTimer -= DeltaTime;
		return;
	}
	
	FPlatformTargetPoint& CurrentData = TargetPoints[CurrentTargetIndex];
	CurrentTarget = CurrentData.Target;
	
	
	float distance = UKismetMathLibrary::Vector_Distance(CurrentTarget->GetActorLocation(), GetActorLocation());

	if (distance < TargetDistance)
	{
		GetNewTarget();
		
		CurrentTarget = TargetPoints[CurrentTargetIndex].Target;

		WaitTimer = TargetPoints[CurrentTargetIndex].WaitTime;

		return;
	}
	
	Super::Tick(DeltaTime);
	MoveToTarget(DeltaTime);*/

	Super::Tick(DeltaTime);

	if (!bTriggered || TargetPoints.Num() == 0) return;
	if (!TargetPoints.IsValidIndex(CurrentTargetIndex)) return;
	if (!IsValid(CurrentTarget)) return;

	if (WaitTimer > 0.f)
	{
		WaitTimer -= DeltaTime;
		return;
	}

	MoveToTarget(DeltaTime);
}

void ABaseMovingPlatform::OnTrigger_Implementation()
{
	ToggleMoving();
	
	ITriggerable::OnTrigger_Implementation();
}

void ABaseMovingPlatform::GetNewTarget_Implementation()
{
	if (TargetPoints.Num() == 0) return;

	CurrentTargetIndex = (CurrentTargetIndex + 1) % TargetPoints.Num();
}

void ABaseMovingPlatform::ToggleMoving_Implementation()
{
	bTriggered = !bTriggered;	
}

/*void ABaseMovingPlatform::MoveToTarget_Implementation(float DeltaTime)
{
	if (!bTriggered || !IsValid(CurrentTarget)) return;

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentTarget->GetActorLocation();
	

	if (bSmoothMovement)
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);

		SetActorLocation(NewLocation);
		return;
	}
	
	FVector direction = (TargetLocation - CurrentLocation).GetSafeNormal();

	float speed = MoveSpeed * DeltaTime;

	AddActorWorldOffset((direction * speed), true);
}*/

void ABaseMovingPlatform::MoveToTarget_Implementation(float DeltaTime)
{
	if (!IsValid(CurrentTarget)) return;

	const FVector TargetLocation = CurrentTarget->GetActorLocation();

	if (!bIsMoving)
	{
		StartLocation = GetActorLocation();
		MoveAlpha = 0.f;
		bIsMoving = true;
	}

	const float Distance = FVector::Distance(StartLocation, TargetLocation);
	if (Distance <= KINDA_SMALL_NUMBER) return;

	//Change MoveAlpha based on speed and distance
	MoveAlpha = FMath::Clamp(MoveAlpha + (MoveSpeed * DeltaTime) / Distance, 0.f, 1.f);

	//Only apply easing if "bSmoothMovement" is true
	const float Alpha = bSmoothMovement ? FMath::InterpEaseInOut(0.f, 1.f, MoveAlpha, 2.f) : MoveAlpha;

	SetActorLocation(FMath::Lerp(StartLocation, TargetLocation, Alpha));

	//Check if reached target
	if (MoveAlpha >= 1.f)
	{
		bIsMoving = false;
		GetNewTarget();
		CurrentTarget = TargetPoints[CurrentTargetIndex].Target;
		WaitTimer = TargetPoints[CurrentTargetIndex].WaitTime;
	}
}
