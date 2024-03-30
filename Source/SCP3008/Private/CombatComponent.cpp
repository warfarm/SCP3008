// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"


UCombatComponent::UCombatComponent()
{	
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// TODO!
bool UCombatComponent::StartBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("player blcoekd"));
	return true;
}

bool UCombatComponent::EndBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("BLCOK ENDED"));
	return true;
}

bool UCombatComponent::TakeDamage(float DamageAmount)
{
	if (bCanTakeDamage)
	{
		Health -= DamageAmount;
		return true;
	}
	if (bIsBlocking)
	{
		// handle parry shing shing thing 
	}
	return false;
}

void UCombatComponent::SetMaxHealth(const float Health_)
{
	MaxHealth = Health_;
	
}

void UCombatComponent::SetCurrentAndMaxHealth(const float Health_)
{
	MaxHealth = Health_;
	Health = Health_;
}

void UCombatComponent::RestoreHealth()
{
	Health = MaxHealth;
}
