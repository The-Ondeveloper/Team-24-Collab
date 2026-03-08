// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Collider.generated.h"


class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorEnterOverlap, AActor*, OverlappedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorExitOverlap, AActor*, OverlappedActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM24PROJECT_API UCollider : public UBoxComponent
{
	GENERATED_BODY()

public:
	UCollider();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	virtual TArray<AActor*> GetOverlappedActors();

	UPROPERTY(BlueprintAssignable)
	FOnActorEnterOverlap OnActorEnterOverlap;

	UPROPERTY(BlueprintAssignable)
	FOnActorExitOverlap OnActorExitOverlap;

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider)
	TArray<AActor*> OverlappedActors;
	
};
