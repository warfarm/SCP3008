// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/MainPlayer.h"
#include "UserInterface/Main/BaseHUD.h"
#include "Components/InventoryComponent.h"

#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BuildableComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "World/Pickup.h"

void AMainPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate combat component
	DOREPLIFETIME(AMainPlayer, CombatComponent);
}

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// PlayerInputComponent = CreateDefaultSubobject<UInputComponent>("default input");

	// init capsule collision
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	
	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(DefaultSlotCapacity);
	PlayerInventory->SetWeightCapacity(DefaultWeightCapacity);

	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	CombatComponent->SetCurrentAndMaxHealth(150.f);
	CombatComponent->SetNetAddressable();
	CombatComponent->SetIsReplicated(true);
}

void AMainPlayer::UpdateInteractionWidget() const
{
	if(IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void AMainPlayer::DropItem(UItemBase* ItemToDrop)
{
	if(PlayerInventory->FindMatchingItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector SpawnLocation{GetActorLocation() + (GetActorForwardVector() * 50.f)};
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		APickup* PickUp = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);

		PickUp->InitializeDrop(ItemToDrop);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was skibidi null"))
	}
}

FVector AMainPlayer::GetCameraPosition()
{
	return Camera->GetComponentLocation();
}

FVector AMainPlayer::GetLookVector()
{
	return GetViewRotation().Vector();
}

std::optional<FHitResult> AMainPlayer::BlockingLookDirRaycast(FCollisionQueryParams& QueryParams, float Distance)
{
	FVector TraceStart{GetCameraPosition()};
	FVector TraceEnd{TraceStart +  GetLookVector() * Distance};

	FHitResult HitResult{};

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		return {HitResult};
	}
	return {};
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->GravityScale = 1.2f;

	HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AMainPlayer::Landed(const FHitResult& Hit)
{
	bIsJumping = false;
}


// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup enhanced input
	auto InputSystem = GetInputSystem();
	if (InputSystem.has_value())
	{
		InputSystem.value()->AddMappingContext(MainInputMapping, 0);
		// TODO! ADD CONTEXT MAPPING every time weapon is pulled out ????
		InputSystem.value()->AddMappingContext(CombatInputMapping, 1);
	}

	// If PlayerInputComponent is an instance of EnhancedInputComponent
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Main action bindings
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayer::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayer::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainPlayer::Jump);
		
		Input->BindAction(SprintAction, ETriggerEvent::Started, this, &AMainPlayer::SprintStart);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainPlayer::SprintEnd);

		Input->BindAction(ToggleAction, ETriggerEvent::Triggered, this, &AMainPlayer::ToggleMenu);
		Input->BindAction(HotBarToggleAction, ETriggerEvent::Triggered, this, &AMainPlayer::ToggleHotBar);
		
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainPlayer::BeginInteract);
		Input->BindAction(InteractAction, ETriggerEvent::Completed, this, &AMainPlayer::EndInteract);

		Input->BindAction(BuildAction, ETriggerEvent::Started, this, &AMainPlayer::Build);

		// Build action bindings
		Input->BindAction(BuildShiftOffsetAction, ETriggerEvent::Triggered, this, &AMainPlayer::BuildShiftOffset);

		// Combat action bindings
		Input->BindAction(BlockAction, ETriggerEvent::Started, this, &AMainPlayer::StartBlock);
		Input->BindAction(BlockAction, ETriggerEvent::Completed, this, &AMainPlayer::EndBlock);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainPlayer::Attack);
	}
}

void AMainPlayer::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if(IsValid(Controller))
	{
		const FVector Forward = GetActorForwardVector();
		const FVector Right = GetActorRightVector();

		float TrueSpeed = MoveSpeed;
		if (bIsSprinting)
		{
			TrueSpeed *= SprintSpeedMultiplier;	
		}

		// update max movepseed or soemthing
		if (PreviousTrueSpeed != TrueSpeed)
		{
			PreviousTrueSpeed = TrueSpeed;
			GetCharacterMovement()->MaxWalkSpeed = TrueSpeed * 600.f;
		}

		// UE_LOG(LogTemp, Warning, TEXT("TRUESPEED IS"));

		AddMovementInput(Forward, InputVector.Y * TrueSpeed);
		AddMovementInput(Right, InputVector.X * TrueSpeed);
	}	
}

void AMainPlayer::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if(IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X * CameraSensitivity);
		AddControllerPitchInput(InputVector.Y * CameraSensitivity);
	}
}

void AMainPlayer::Jump()
{
	if (!bIsJumping && Stamina >= JumpStaminaCost)
	{
		Stamina -= JumpStaminaCost;

		// for some reason jump power scales insanely low
		GetCharacterMovement()->JumpZVelocity = JumpPower * 500;
		ACharacter::Jump();

		// this is set to false in the Landed(...) override
		bIsJumping = true;
	}
}

void AMainPlayer::SprintStart()
{
	bIsSprinting = true;
}

void AMainPlayer::SprintEnd()
{
	bIsSprinting = false;
}

// TODO!
void AMainPlayer::Build()
{
	UE_LOG(LogTemp, Warning, TEXT("BUILD TRIGGERED"));
	
	bool bIsHolding = CurrentHeldBuildable != nullptr;

	auto InputSystem = GetInputSystem();
	if (!InputSystem.has_value())
	{
		// something went wrong
		return;
	}
	
	if (bIsHolding)
	{
		// logic for placing down stuff
		CurrentHeldBuildable->PlaceDown();

		CurrentHeldBuildable = nullptr;
		InputSystem.value()->RemoveMappingContext(BuildInputMapping);
		UE_LOG(LogTemp, Warning, TEXT("PLACED"));
	}
	else
	{
		// logic for picking stuff

		// perform raycast
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
	
		std::optional<FHitResult> HitResultOption = BlockingLookDirRaycast(QueryParams, InteractionCheckDistance);

		if (!HitResultOption.has_value())
		{
			return;
		}

		AActor* HitActor = HitResultOption.value().GetActor();
		UActorComponent* RetrievedBuildableComponent =
			HitActor->GetComponentByClass(UBuildableComponent::StaticClass());
		if (!RetrievedBuildableComponent)
		{
			return;
		}
		if (UBuildableComponent* TargetedBuildable = CastChecked<UBuildableComponent>(RetrievedBuildableComponent))
		{
			// player has tried to interact w a buildable
			
			TargetedBuildable->PickUp(this);
			CurrentHeldBuildable = TargetedBuildable;
			InputSystem.value()->AddMappingContext(BuildInputMapping, 1);
			UE_LOG(LogTemp, Warning, TEXT("PICKED UP"));
		}
		// if not we dont need to do anything
	}
}

void AMainPlayer::BuildShiftOffset(const FInputActionValue& InputValue)
{
	float Input = InputValue.Get<float>();

	bool bIsHolding = CurrentHeldBuildable != nullptr;

	if (bIsHolding)
	{
		CurrentHeldBuildable->ShiftOffsetPercent(1.f + Input/7.f);
	}
}

void AMainPlayer::StartBlock()
{
	CombatComponent->StartBlock();
}

void AMainPlayer::EndBlock()
{
	CombatComponent->EndBlock();
}

void AMainPlayer::Attack()
{
	// TODO! raycast shit
	FCollisionQueryParams QueryParams{};
	QueryParams.AddIgnoredActor(this);
	// I DONT PLAY DEEPWOKEN
	std::optional HitResultOption = BlockingLookDirRaycast(QueryParams, 1000);
	if (!HitResultOption.has_value())
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("u didnt hit anything dipshit")));
		return;
	}
	AActor* HitActor = HitResultOption.value().GetActor();
	UActorComponent* RetrievedCombatComponent =
		HitActor->GetComponentByClass(UCombatComponent::StaticClass());
	if (!RetrievedCombatComponent)
	{
		return;
	}
	if (UCombatComponent* TargetedEnemy = CastChecked<UCombatComponent>(RetrievedCombatComponent))
	{
		EAttackResult AttackResult = CombatComponent->DoAttackOn(TargetedEnemy);

		switch (AttackResult)
		{
		case Parried:
			{
				break;
			}
		case Blocked:
			{
				break;
			}
		case BlockBroken:
			{
				break;
			}
		case Immune:
			{
				break;
			}
		case Success:
			{
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("shing shing shing")));
				break;
			}
		case CannotAttackNow:
			{
				break;
			}
		case Unknown:
			{
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("UNKNONW?? FIX YO CODE")));
				break;
			}
		default:
			{
				if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("idk what happeend here ur cooked")));
				break;
			}
		}
	}
}

std::optional<UEnhancedInputLocalPlayerSubsystem*> AMainPlayer::GetInputSystem()
{
	// Setup enhanced input
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			return {Subsystem};
		}
	}
	return {};
}

void AMainPlayer::ToggleMenu()
{
	HUD->ToggleMenu();
}

void AMainPlayer::ToggleHotBar()
{
	HUD->ToggleHotBar();
}

void AMainPlayer::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	if (USceneComponent* CameraComponent = CastChecked<USceneComponent>(Camera))
	{
	 	FVector TraceStart{GetCameraPosition()};
	 	FVector TraceEnd{TraceStart +  GetLookVector() * InteractionCheckDistance};
	//
	// 	// TODO! remove later
	 	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0.f, 2.f);
	
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		std::optional<FHitResult> HitResultOption{BlockingLookDirRaycast(QueryParams, InteractionCheckDistance)};

		if (HitResultOption.has_value())
		{ //UE_LOG(LogTemp, Warning, TEXT("Result Valid"))
			FHitResult const& HitResult = HitResultOption.value();
			AActor* HitActor = HitResult.GetActor();
			//UE_LOG(LogTemp, Warning, TEXT("Reparsed Found AActor"))
			// Checks to see if the actor class itself implements UInteractionIterface
			if (HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{//UE_LOG(LogTemp, Warning, TEXT("Found Implementation"))
				// If we are looking at the same interactable for some reason
				if (HitActor != InteractionData.CurrentInteractable)
				{//UE_LOG(LogTemp, Warning, TEXT("Found Interactable"))
					FoundInteractable(HitActor);
					return;
				}
				if (HitActor == InteractionData.CurrentInteractable)
				{//UE_LOG(LogTemp, Warning, TEXT("Found Interactable"))
					return;
				}
				
			}
		}
	}

	NoInteractableFound();
}

void AMainPlayer::FoundInteractable(AActor* NewInteractable)
{
	//UE_LOG(LogTemp, Warning, TEXT("1Found Interactable"))
	if (IsInteracting())
	{
		EndInteract();
	}
	//UE_LOG(LogTemp, Warning, TEXT("2Attempting to Get New Interactable"))
	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}
	
	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	//Update Interaction Widget
	//UE_LOG(LogTemp, Warning, TEXT("3ATTEMPTING TO SHOW HUD"))
	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	
	TargetInteractable->BeginFocus();
}

void AMainPlayer::NoInteractableFound()
{//UE_LOG(LogTemp, Warning, TEXT("Found No Interactable"))
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		// hide interaction widget on the HUD
		HUD->HideInteractionWidget();
		
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void AMainPlayer::BeginInteract()
{
	// verify nothing has changed with the interactable state since beginning interaction
	PerformInteractionCheck();
	//UE_LOG(LogTemp, Warning, TEXT("Interaction Check Performed"))
	if (InteractionData.CurrentInteractable)
	{ //UE_LOG(LogTemp, Warning, TEXT("Found Interactable in Begin Interact"))
		if (IsValid(TargetInteractable.GetObject()))
		{ //UE_LOG(LogTemp, Warning, TEXT("Valid Object Found"))
			TargetInteractable->BeginInteract();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&AMainPlayer::Interact,
					false);	
			}
		}
	}
}

void AMainPlayer::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AMainPlayer::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}