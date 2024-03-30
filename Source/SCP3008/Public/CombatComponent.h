// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCP3008_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	/* ----- ATTRIBUTES ----- */
	UPROPERTY(EditAnywhere, Category="Combat | Stats")
	float MaxHealth{ 100.f };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat | Stats")
	float Health{ MaxHealth };
	UPROPERTY(EditAnywhere, Category="Combat | General")
	// not frames, measured in seconds
	float ParryFrames{ 0.2f };
	// UPROPERTY(EditAnywhere, Category="Combat | General")
	// float DodgeFrames{ 0.4f };

	/* ----- STATE ----- */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat | State")
	bool bIsBlocking{ false };
	UPROPERTY(EditAnywhere, Category="Combat | State")
	bool bCanTakeDamage{ true };
	std::map<std::string, FTimerHandle> TickDamageSources;
	std::map<std::string, float> DamageMultiplierSources;
	
	virtual void BeginPlay() override;

public:
	UCombatComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// This is a parry until parry frames are finished, then block..
	bool StartBlock();
	bool EndBlock();
	bool TakeDamage(float DamageAmount);
	// Does not change current health.
	FORCEINLINE void SetMaxHealth(float Health);
	FORCEINLINE void SetCurrentAndMaxHealth(float Health);
	FORCEINLINE void RestoreHealth();
		
};
