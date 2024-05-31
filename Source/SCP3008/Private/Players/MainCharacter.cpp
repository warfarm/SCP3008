// Fill out your copyright notice in the Description page of Project Settings.


#include "SCP3008/Public/Players/MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "FindInBlueprints.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

#define ENABLE_DEBUG_MODE

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorTickInterval(0.5f);
	SetActorTickEnabled(true);
	
	// Create Camera SubObject
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	//Set up and attach to RootComponent
	//Camera->SetupAttachment(RootComponent);
	//Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(GetMovementComponent())
	{
		GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? RunningMaxSpeed : NormalWalkSpeed;
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}
}

void AMainCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{

	if(bIsRunning && CurrentStamina <= 0)
	{
		SetRunning(false);
	}
	
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);

	if(bIsRunning)
	{
		bHasRan = true;
	}
}

void AMainCharacter::Jump()
{
	UnCrouch();
	Super::Jump();
	bHasJumped = true;
}

void AMainCharacter::Crouch(bool bClientSimulation)
{
	SetRunning(false);
	Super::Crouch(bClientSimulation);
}

void AMainCharacter::SetRunning(bool IsRunning)
{
	bIsRunning = IsRunning;

	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? RunningMaxSpeed : NormalWalkSpeed;
}

void AMainCharacter::ToggleRunning()
{
	SetRunning(!bIsRunning);
}

void AMainCharacter::SetHasJumped(bool HasJumped)
{
	bHasJumped = HasJumped;
}

void AMainCharacter::SetHasRan(bool HasRan)
{
	bHasRan = HasRan;
}

int AMainCharacter::GetHealth()
{
	return CurrentHealth;
}

int AMainCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void AMainCharacter::UpdateHealth(int DeltaHealth)
{
	//Check if player is alive
	if (CurrentHealth <= 0.0f)
	{
		return;
	}

	int OldValue = CurrentHealth;

	CurrentHealth += DeltaHealth;
	//Clamp Health
	FMath::Clamp(CurrentHealth, -1.0f, GetMaxHealth());

	//If Health changed, Broadcast Update
	if(CurrentHealth != OldValue)
	{
		OnHealthChanged.Broadcast(OldValue, CurrentHealth, MaxHealth);
	}

	//Check if Player Just died
	if(CurrentHealth <= 0.0f)
	{
		OnPlayerDeath.Broadcast();
	}
}

void AMainCharacter::SetMaxHealth(int NewMaxHealth)
{
	int OldValue = MaxHealth;

	MaxHealth = NewMaxHealth;

	if(MaxHealth != OldValue)
	{
		if(MaxHealth < OldValue)
		{
			if(CurrentHealth > MaxHealth)
			{
				CurrentStamina = MaxHealth;
			}
		}
		OnHealthChanged.Broadcast(OldValue, CurrentHealth, MaxHealth);
	}
}

float AMainCharacter::GetStamina()
{
	return CurrentStamina;
}

float AMainCharacter::GetStaminaRegenerationFactor()
{
	return StaminaRegenFactor;
}

void AMainCharacter::SetStaminaRegenerationFactor(float NewRegenerationFactor)
{
	StaminaRegenFactor = NewRegenerationFactor;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region StaminaTick

	float RealStaminaRegenerationFactor = StaminaRegenFactor;

	if (bIsCrouched)
	{
		RealStaminaRegenerationFactor=RestStaminaFactor;
	}

	const float PreviousStamina = CurrentStamina;

	CurrentStamina = FMath::Clamp(CurrentStamina + RealStaminaRegenerationFactor, 0.f, MaxStamina);

	if (CurrentStamina != PreviousStamina)
	{
		OnStaminaChanged.Broadcast(PreviousStamina, CurrentStamina, MaxStamina);
	}

	SetHasRan(false);
	SetHasJumped(false);
	
#pragma endregion

#ifdef ENABLE_DEBUG_MODE

	GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Silver,
		*(FString::Printf(TEXT("Movement: IsCrouched[%d] | IsRunning[%d]"), bIsCrouched, bIsRunning)));
	GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Red,
		*(FString::Printf(TEXT("Health: CurrentHealth[%d] | MaxHealth[%d]"), GetHealth(), GetMaxHealth())));
	GEngine->AddOnScreenDebugMessage(-1, 0.49f, FColor::Green,
		*(FString::Printf(TEXT("Stamina: CurrentStam[%f] | MaxStam[%f]"), GetStamina(), MaxStamina)));
	
#endif
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
