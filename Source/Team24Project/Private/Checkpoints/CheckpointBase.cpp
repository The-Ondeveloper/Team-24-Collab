// Fill out your copyright notice in the Description page of Project Settings.


#include "Team24Project/Public/Checkpoints/CheckpointBase.h"

#include "Team24Project/Public/Components/Collider.h"


// Sets default values
ACheckpointBase::ACheckpointBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCollider>("Collider");
	SetRootComponent(Collider);
	Collider->OnActorEnterOverlap.AddUniqueDynamic(this, &ACheckpointBase::OnColliderTrigger);
	Collider->OnActorExitOverlap.AddUniqueDynamic(this, &ACheckpointBase::CheckpointDeactivated);

}

// Called when the game starts or when spawned
void ACheckpointBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpointBase::CheckpointActivated_Implementation(AActor* OverlappedActor)
{
	if (OnCheckPointActivated.IsBound()) OnCheckPointActivated.Broadcast();
}

void ACheckpointBase::CheckpointDeactivated_Implementation(AActor* OverlappedActor)
{
	if (OnCheckPointDeactivated.IsBound()) OnCheckPointDeactivated.Broadcast();
}

void ACheckpointBase::OnColliderTrigger(AActor* OverlappedActor)
{	
	if (!OverlappedActor->ActorHasTag("Player") && bPlayerOnly) return;

	if (bTriggersOnlyOnce && bHasTriggered) return;

	bHasTriggered = true;
	CheckpointActivated(OverlappedActor);
}

// Called every frame
void ACheckpointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

