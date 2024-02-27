// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "Logging/LogMacros.h"
#include "MainPlayer.generated.h"

class ABaseHUD;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() :
	CurrentInteractable(nullptr),
	LastInteractionCheckTime(0.f)
	{
		
	}

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
	
};

UCLASS()
class SCP3008_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	/* ----- COMPONENTS ----- */

	UPROPERTY()
	ABaseHUD* HUD;
	
	// Input stuff
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	class UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	UInputAction* SprintAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	UInputAction* InteractAction;

	// Camera
	UPROPERTY(EditAnywhere, Category="Player | Camera")
	UCameraComponent* Camera;
	
	// Gameplay
	UPROPERTY(VisibleAnywhere, Category="Player | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;
	
	// TODO! insert health component here

	/* ----- PROPERTIES ----- */
	
	// Hunger, Thirst, Stamina
	UPROPERTY(EditAnywhere, Category="Player | Core")
	float MaxHunger{ 100.f };
	UPROPERTY(EditAnywhere, Category="Player | Core")
	float MaxThirst{ 100.f };
	UPROPERTY(EditAnywhere, Category="Player | Core")
	float MaxStamina{ 125.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player | Core")
	float Hunger{ MaxHunger };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player | Core")
	float Thirst{ MaxThirst };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player | Core")
	float Stamina{ MaxStamina };

	UPROPERTY(EditAnywhere, Category="Player | Core")
	float JumpStaminaCost{ 5.f };

	// Movement Related
	UPROPERTY(EditAnywhere, Category="Player | Movement")
	float MoveSpeed{ 1.f };	

	UPROPERTY(EditAnywhere, Category="Player | Movement")
	float SprintSpeedMultiplier{ 1.33f };
	
	UPROPERTY(EditAnywhere, Category="Player | Movement")
	float JumpPower{ 1.f };

	// Camera
	float CameraSensitivity{ 0.8f };

	// Interactions
	float InteractionCheckFrequency{ 0.1f };
	float InteractionCheckDistance{ 300.f };

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;
	
	/* ----- STATE ----- */
	
	bool bIsJumping{ false };
	bool bIsSprinting{ false };
	float PreviousTrueSpeed{ MoveSpeed };

	/* ----- OVERRIDES ----- */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* ----- INPUT RELATED ----- */
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
	void SprintStart();
	void SprintEnd();

	/* ----- INTERACTIONS ----- */
	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }
	
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

};
