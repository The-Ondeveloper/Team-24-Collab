// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BaseInteractable.h"

#include "Components/Collider.h"
#include "Interfaces/Triggerable.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCollider>("Collider");
	SetRootComponent(Collider);

	Collider->bEditableWhenInherited = true;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseInteractable::OnInteractableBeginOverlap(AActor* OverlappedActor)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		UFunction* Func = PC->FindFunction(TEXT("AddNewInteractable"));

		if (Func)
		{
			struct FAddInteractableParams
			{
				AActor* Actor;
			};

			FAddInteractableParams Params;
			Params.Actor = this;
		
			PC->ProcessEvent(Func, &Params);
		}
	}
}

void ABaseInteractable::OnInteractableEndOverlap(AActor* OtherActor)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		UFunction* Func = PC->FindFunction(TEXT("RemoveInteractable"));

		if (Func)
		{
			struct FAddInteractableParams
			{
				AActor* Actor;
			};

			FAddInteractableParams Params;
			Params.Actor = this;
		
			PC->ProcessEvent(Func, &Params);
		}
	}
}

void ABaseInteractable::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Collider)
	{
		Collider->OnActorEnterOverlap.RemoveDynamic(this, &ThisClass::OnInteractableBeginOverlap);
		Collider->OnActorEnterOverlap.AddDynamic(this, &ThisClass::OnInteractableBeginOverlap);
		
		Collider->OnActorExitOverlap.RemoveDynamic(this, &ThisClass::OnInteractableEndOverlap);
		Collider->OnActorExitOverlap.AddDynamic(this, &ThisClass::OnInteractableEndOverlap);
	}
}

void ABaseInteractable::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

