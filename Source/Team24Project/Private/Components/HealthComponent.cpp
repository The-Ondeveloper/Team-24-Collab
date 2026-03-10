#include "Components/HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	BroadcastChange();

	if (AActor* Owner = Cast<AActor>(GetOwner()))
	{
		Owner->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::OnDamageDealt);
	}
}

void UHealthComponent::OnDamageDealt(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth <= 0) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	//On healing
	if (Damage < 0)
	{
		if (OnReceiveHealing.IsBound())
		{
			OnReceiveHealing.Broadcast(-Damage);
		}
		
		BroadcastChange();
		
		return;
	}

	//if player died
	if (CurrentHealth <= 0.0f && OnDeath.IsBound())
	{
		OnDeath.Broadcast();
	}

	
	if (OnTakeDamage.IsBound())
	{
		OnTakeDamage.Broadcast(Damage);	
	}

	BroadcastChange();
	
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UHealthComponent::GetHealthPercent()
{
	return CurrentHealth / MaxHealth;
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UHealthComponent::BroadcastChange()
{
	if (OnHealthChange.IsBound())
	{
		OnHealthChange.Broadcast(CurrentHealth);
	}
}

