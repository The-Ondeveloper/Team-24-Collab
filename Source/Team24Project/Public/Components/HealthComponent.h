// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceiveHealing, float, Healing);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM24PROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Health")
	FOnHealthChange OnHealthChange;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Health")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Health")
	FOnTakeDamage OnTakeDamage;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Health")
	FOnReceiveHealing OnReceiveHealing;
	
	UFUNCTION(BlueprintCallable, Category="Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category="Health")
	float GetMaxHealth();
	
	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealthPercent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDamageDealt(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health")
	float MaxHealth = 100;

	UPROPERTY(BlueprintReadWrite, Category="Health")
	float CurrentHealth;
	
private:
	void BroadcastChange();
};
