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
}

void AMainPlayer::UpdateInteractionWidget() const
{
	if(IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

FVector AMainPlayer::GetCameraLocation()
{
	return Camera->GetComponentLocation();
}

FVector AMainPlayer::GetLookVector()
{
	return GetViewRotation().Vector();
}

std::optional<FHitResult> AMainPlayer::BlockingLookDirRaycast(FCollisionQueryParams& QueryParams, float Distance)
{
	FVector TraceStart{GetCameraLocation()};
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
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	// If PlayerInputComponent is an instance of EnhancedInputComponent
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayer::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayer::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainPlayer::Jump);
		
		Input->BindAction(SprintAction, ETriggerEvent::Started, this, &AMainPlayer::SprintStart);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainPlayer::SprintEnd);
		
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainPlayer::BeginInteract);
		Input->BindAction(InteractAction, ETriggerEvent::Completed, this, &AMainPlayer::EndInteract);
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

		UE_LOG(LogTemp, Warning, TEXT("TRUESPEED IS %f"), TrueSpeed);

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
	bool bIsHolding = CurrentHeldBuildable != nullptr;

	if (bIsHolding)
	{
		// logic for placing down stuff
		CurrentHeldBuildable->PlaceDown();
	}
	else
	{
		// logic for picking stuff 
		UBuildableComponent* TargetBuildable;
		TargetBuildable->PickUp(this);
	}
}

void AMainPlayer::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	if (USceneComponent* CameraComponent = CastChecked<USceneComponent>(Camera))
	{
		FVector TraceStart{GetCameraLocation()};
		FVector TraceEnd{TraceStart +  GetLookVector() * InteractionCheckDistance};

		// TODO! remove later
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0.f, 2.f);
	
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		std::optional<FHitResult> HitResultOption{BlockingLookDirRaycast(QueryParams, InteractionCheckDistance)};

		if (HitResultOption.has_value())
		{
			FHitResult const& HitResult = HitResultOption.value();
			AActor* HitActor = HitResult.GetActor();

			// Checks to see if the actor class itself implements UInteractionIterface
			if (HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{
				// If we are looking at the same interactable for some reason
				if (HitActor == InteractionData.CurrentInteractable)
				{
					return;
				}
				FoundInteractable(HitActor);
			}
		}
	}

	NoInteractableFound();
}

void AMainPlayer::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	//Update Interaction Widget
	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	
	TargetInteractable->BeginFocus();
}

void AMainPlayer::NoInteractableFound()
{
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

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
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


