// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ButtonBase.h"

#include "Components/Collider.h"
#include "Interfaces/Triggerable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AButtonBase::AButtonBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AButtonBase::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Button pressed")));

	if (bInteracted)
	{
		bInteracted = false;
		//play toggle-off sound
	}
	else
	{
		bInteracted = true;
		//play toggle on sound
	}

	if (TriggerTargets.Num() <= 0) return;

	for (auto target : TriggerTargets)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(target, UTriggerable::StaticClass()))
		{
			ITriggerable::Execute_OnTrigger(target);
		}
	}

	IInteractable::Interact_Implementation();
}

