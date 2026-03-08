#include "Team24Project/Public/Components/Collider.h"


UCollider::UCollider()
{
	PrimaryComponentTick.bCanEverTick = true;

	this->OnComponentBeginOverlap.AddDynamic(this, &UCollider::OnOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
	
}


// Called when the game starts
void UCollider::BeginPlay()
{
	Super::BeginPlay();
}


void UCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollider::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AActor* actor = CastChecked<AActor>(OtherActor))
	{
		OverlappedActors.Add(actor);
		OnActorEnterOverlap.Broadcast(actor);
	}
}

void UCollider::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		OverlappedActors.Remove(OtherActor);
	}
	
	OnActorExitOverlap.Broadcast(OtherActor);	
}

TArray<AActor*> UCollider::GetOverlappedActors()
{
	return OverlappedActors;
}

