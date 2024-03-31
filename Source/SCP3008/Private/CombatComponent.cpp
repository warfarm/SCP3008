// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"


UCombatComponent::UCombatComponent()
{	
}

void UCombatComponent::TransitionToBlockStateFromParry()
{
	BlockState = Blocking;
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("PARRY -> BLOCK")));
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
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("BLOCK START")));
	BlockState = Parrying;
	GetOwner()->GetWorldTimerManager().SetTimer(
		TransitionToBlockHandle,
		this,
		&UCombatComponent::TransitionToBlockStateFromParry,
		ParryFrames,
		false
	);
	return true;
}

bool UCombatComponent::EndBlock()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("BLOCK END")));
	BlockState = None;
	GetOwner()->GetWorldTimerManager().ClearTimer(TransitionToBlockHandle);
	return true;
}

bool UCombatComponent::TakeDamage(float DamageAmount, float PostureDamageAmount)
{
	if (bCanTakeDamage || BlockState == None)
	{
		Health -= DamageAmount;
		return true;
	}
	switch (BlockState)
	{
	case Parrying:
		{
			// handle parry shing shing thing
			Posture = Posture - PostureRestoreOnParry < 0.f ? 0.f : Posture - PostureRestoreOnParry; 
		}
	case Blocking:
		{
			// handle block clunk ncluink
			if (Posture == MaxPosture)
			{
				// TODO! guardbreak
				Posture = 0.f;
			}
			else
			{
				Posture = Posture + PostureDamageAmount > MaxPosture ? MaxPosture : Posture + PostureDamageAmount; 
			}
		}
	default:
		{
			// wtf happened for you to get here?
			// you deserve a segfault.
			int x = *(int*)(0x0);
			printf("%d", x);
		}
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
