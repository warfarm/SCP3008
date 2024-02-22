// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MainPlayer.generated.h"

UCLASS()
class SCP3008_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	/* ----- COMPONENTS ----- */
	// Input stuff
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	class UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* SprintAction;

	// Camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	// Gameplay
	// TODO! insert health component here

protected:
	/* ----- PROPERTIES ----- */
	
	// Hunger, Thirst, Stamina
	UPROPERTY(EditAnywhere, Category="PlayerCore")
	float MaxHunger{ 100.f };
	UPROPERTY(EditAnywhere, Category="PlayerCore")
	float MaxThirst{ 100.f };
	UPROPERTY(EditAnywhere, Category="PlayerCore")
	float MaxStamina{ 125.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PlayerCore")
	float Hunger{ MaxHunger };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PlayerCore")
	float Thirst{ MaxThirst };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PlayerCore")
	float Stamina{ MaxStamina };

	UPROPERTY(EditAnywhere, Category="PlayerCore")
	float JumpStaminaCost{ 5.f };

	// Movement Related
	UPROPERTY(EditAnywhere, Category="PlayerMovement")
	float MoveSpeed{ 1.f };	

	UPROPERTY(EditAnywhere, Category="PlayerMovement")
	float SprintSpeedMultiplier{ 1.33f };
	
	UPROPERTY(EditAnywhere, Category="PlayerMovement")
	float JumpPower{ 1.f };

	// Camera
	float CameraSensitivity{ 0.8f };

protected:
	/* ----- STATE ----- */
	bool bIsJumping{ false };
	bool bIsSprinting{ false };
	
public:
	// Sets default values for this character's properties
	AMainPlayer();

	/* ----- ACCESSORS ----- */
	// Max values
	inline float GetMaxHunger() const { return MaxHunger; }
	inline float GetMaxThirst() const { return MaxThirst; }
	inline float GetMaxStamina() const { return MaxStamina; }

	// Current values
	inline float GetHunger() const { return Hunger; }
	inline float GetThirst() const { return Thirst; }
	inline float GetStamina() const { return Stamina; }
	
protected:
	/* ----- OVERRIDES ----- */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/* ----- INPUT RELATED ----- */
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
	void SprintStart();
	void SprintEnd();
	
};
