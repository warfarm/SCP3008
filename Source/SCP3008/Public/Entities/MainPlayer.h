// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <optional>

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/BuildableComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "Logging/LogMacros.h"
#include "MainPlayer.generated.h"

class UItemBase;
class UInventoryComponent;
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

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category="Character | Inventory")
	UInventoryComponent* PlayerInventory;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Character | HotBar")
	UInventoryComponent* PlayerHotBar;
	
	UPROPERTY()
	ABaseHUD* HUD;
	
	/* ----- INPUT ACTIONS ----- */
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	class UInputMappingContext* MainInputMapping;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	UInputMappingContext* BuildInputMapping;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput")
	UInputMappingContext* CombatInputMapping;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* ToggleAction;

	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* HotBarToggleAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | MainActions")
	UInputAction* BuildAction;

	// Will only be present in build mode
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | BuildActions")
	UInputAction* BuildShiftOffsetAction;

	// Will only be present while having a weapon equipped.
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | CombatActions")
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | CombatActions")
	UInputAction* BlockAction;

	// HotBar Slot
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | HotbarSlot")
	UInputAction* HotBarSlot1;

	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | HotbarSlot")
	UInputAction* HotBarSlot2;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | HotbarSlot")
	UInputAction* HotBarSlot3;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | HotbarSlot")
	UInputAction* HotBarSlot4;
	
	UPROPERTY(EditAnywhere, Category="Player | EnhancedInput | HotbarSlot")
	UInputAction* HotBarSlot5;

	// HOTBAR FUNCTIONALITY
	UPROPERTY(VisibleAnywhere, Category = "Player | HotBar")
	UItemBase* CurrentItem;
	
	/* ----- INPUT RELATED ----- */
	FInputActionBinding PlayerActionBinding;
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
	void SprintStart();
	void SprintEnd();
	void Build();
	void BuildShiftOffset(const FInputActionValue& InputValue);
	// Block is a parry until parry frames are finished, then degrades into block.
	void StartBlock();
	void EndBlock();
	void Attack();
	
	// Camera
	UPROPERTY(EditAnywhere, Category="Player | Camera")
	UCameraComponent* Camera;
	
	// Gameplay
	UPROPERTY(VisibleAnywhere, Category="Player | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Player | Combat")
	UCombatComponent* CombatComponent{};
	
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

	UBuildableComponent* CurrentHeldBuildable;

	// Default Inventory Statistics
	int32 DefaultSlotCapacity{ 20 };
	float DefaultWeightCapacity{ 50 };

	// Default HotBar Statistics
	int32 DefaultHotBarCapacity{ 5 };
	float DefaultHotBarWeightCapacity{ 15 };
	/* ----- STATE ----- */
	
	bool bIsJumping{ false };
	bool bIsSprinting{ false };
	float PreviousTrueSpeed{ MoveSpeed };
	float BuildOffset{};

	/* ----- OVERRIDES ----- */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// avoid a shit ton of if elses and casts
	std::optional<UEnhancedInputLocalPlayerSubsystem*> GetInputSystem();

	/* ----- INTERACTIONS ----- */
	void ToggleMenu();
	void ToggleHotBar();
	
	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }

	// HotBar Item Functionality
	void ReturnHotBarSlot(int SlotNumber);
	
	/* ----- NETWORKING ----- */
	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	// Sets default values for this character's properties
	AMainPlayer();

	/* ----- ACCESSORS ----- */
	// Max values
	FORCEINLINE float GetMaxHunger() const { return MaxHunger; }
	FORCEINLINE float GetMaxThirst() const { return MaxThirst; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

	// Current values
	FORCEINLINE float GetHunger() const { return Hunger; }
	FORCEINLINE float GetThirst() const { return Thirst; }
	FORCEINLINE float GetStamina() const { return Stamina; }

	FORCEINLINE UInventoryComponent* GetInventory() const {return PlayerInventory;}
	FORCEINLINE UInventoryComponent* GetHotBar() const {return PlayerHotBar;}

	// CurrentHeldItem
	FORCEINLINE UItemBase* GetCurrentItem() const {return CurrentItem;}
	FORCEINLINE void SetCurrentItem(UItemBase* ItemToSet) {CurrentItem = ItemToSet;}
	
	/* ----- FUNCTIONS ----- */
	void UpdateInteractionWidget() const;

	void DropItem(UItemBase* ItemToDrop);

	/* ----- JUST nice stuff to have tbh ----- */
	FORCEINLINE FVector GetCameraPosition();
	FORCEINLINE FVector GetLookVector();
	FORCEINLINE std::optional<FHitResult> BlockingLookDirRaycast(FCollisionQueryParams& QueryParams, float Distance);
};
