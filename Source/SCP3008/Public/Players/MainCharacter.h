// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "MainCharacter.generated.h"

//Delegate for stat changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIntStatUpdated, int32, OldValue, int32, NewValue, int32, MaxValue);

//Delegate for Player Death
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerIsDead);

//Delegate for float Stats Changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFloatStatUpdated, float, OldValue, float, NewValue, float, MaxValue);

class UInputAction;
class UInputMappingContext;
UCLASS()
class SCP3008_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere)
	//class UCameraComponent* Camera;
	
public:

	//Override existing Movement
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;
	virtual void Jump() override;
	virtual void Crouch(bool bClientSimulation = false) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Movement", meta = (AllowPrivateAccess = "true"))
	float NormalWalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Movement", meta = (AllowPrivateAccess = "true"))
	float RunningMaxSpeed = 800.0f;

	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void SetRunning(bool IsRunning);
	
	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void ToggleRunning();

	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void SetHasJumped(bool HasJumped);

	UFUNCTION(BlueprintCallable, Category="Player|Movement")
	void SetHasRan(bool HasRan);
	
#pragma region Health

	UFUNCTION(BlueprintPure, Category="Player|Health")
	int GetHealth();

	UFUNCTION(BlueprintPure, Category="Player|Health")
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category="Player|Health")
	void UpdateHealth(int DeltaHealth);

	UFUNCTION(BlueprintCallable, Category="Player|Health")
	void SetMaxHealth(int NewMaxHealth);

	UPROPERTY(BlueprintAssignable, Category="Player|Health")
	FIntStatUpdated OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Player|Health")
	FPlayerIsDead OnPlayerDeath;
	
#pragma endregion

#pragma region Stamina

	UFUNCTION(BlueprintPure, Category="Player|Stamina")
	float GetStamina();

	UFUNCTION(BlueprintPure, Category="Player|Stamina")
	float GetStaminaRegenerationFactor();

	UFUNCTION(BlueprintCallable, Category="Player|Stamina")
	void SetStaminaRegenerationFactor(float NewRegenerationFactor);

	UPROPERTY(BlueprintAssignable, Category="Player|Stamina")
	FFloatStatUpdated OnStaminaChanged;
	
#pragma endregion
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	//Is Player Running?
	bool bIsRunning = false;

	//Has Player Ran since last check?
	bool bHasRan = false;

	//Has Player Jumped since last check
	bool bHasJumped = false;

	//Health
	static constexpr int BaseHealthValue = 100;
	int MaxHealth = BaseHealthValue;
	int CurrentHealth = BaseHealthValue;

	//Stamina
	static constexpr float MaxStamina = 100.0f;
	static constexpr float RunStaminaCost = 4.0f;
	static constexpr float RestStaminaFactor = 3.0f;
	float StaminaRegenFactor = 2.0f;
	float CurrentStamina = MaxStamina;
};
