// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/MainPlayer.h"

#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->GravityScale = 1.2f;
}

void AMainPlayer::Landed(const FHitResult& Hit)
{
	bIsJumping = false;
}


// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
	}
}

void AMainPlayer::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if(IsValid(Controller))
	{
		const FVector Forward = GetActorForwardVector();
		const FVector Right = GetActorRightVector();

		AddMovementInput(Forward, InputVector.Y * MoveSpeed);
		AddMovementInput(Right, InputVector.X * MoveSpeed);
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

