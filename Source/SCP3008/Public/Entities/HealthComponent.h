 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// USTRUCT()
// struct 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCP3008_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	/* ----- ATTRIBUTES ----- */
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth{ 100 };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	float Health{ MaxHealth };

	
	
public:	
	// Sets default values for this component's properties
	UHealthComponent();

	/* ----- ACCESSORS ----- */
	FORCEINLINE float GetHealth() const { return Health; }
	
protected:
	/* ----- OVERRIDES ----- */
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Returns true if damage was taken, otherwise returns false
	bool TakeDamage(float DamageAmount);

	// will add later if needed 
	// void TakeTickDamage();
};
