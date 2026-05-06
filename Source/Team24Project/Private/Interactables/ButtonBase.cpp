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

	TriggerSound = CreateDefaultSubobject<USoundBase>("Trigger Sound Effect");
	UnTriggerSound = CreateDefaultSubobject<USoundBase>("UnTrigger Sound Effect");
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();

	if (bToggleTriggers)
		bInteracted = bStartTriggered;
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AButtonBase::Interact_Implementation()
{
	

	if (bInteracted && bToggleTriggers)
	{
		bInteracted = false;
		UGameplayStatics::PlaySoundAtLocation(this, UnTriggerSound, GetActorLocation());
	}
	else
	{
		bInteracted = true;
		UGameplayStatics::PlaySoundAtLocation(this, TriggerSound, GetActorLocation());
	}

	if (TriggerTargets.Num() <= 0) return;

	for (auto target : TriggerTargets)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(target, UTriggerable::StaticClass()))
		{
			if (bInteracted)
			{
				ITriggerable::Execute_OnTrigger(target);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("triggered")));
			}
			else
			{
				ITriggerable::Execute_OnUnTrigger(target);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Untriggered")));
			}
		}
	}

	IInteractable::Interact_Implementation();
}

