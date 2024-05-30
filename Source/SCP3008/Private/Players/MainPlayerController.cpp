// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Players/MainCharacter.h"

// NATIVE FUNCTIONS
void AMainPlayerController::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);

	//Set Reference to Player pawn/Character
	PlayerCharacter = Cast<AMainCharacter>(APawn);
	checkf(PlayerCharacter, TEXT("PlayerCharacter OnPossess Fail"));
	
	//Get Reference to Enhanced Input Component
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("EnhancedInputComponent OnPosses Fail"));

	//Get Local Player subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("UEInput Get LocalPlayer OnPosses Fail"))

	//Check if InputMapping Exists
	checkf(InputMappingContent, TEXT("No InputMappingContent specified"))
	InputSubsystem->ClearAllMappings();
	//Add Mapping Context with context priority
	InputSubsystem->AddMappingContext(InputMappingContent, 0);
	//Bind InputActions
	// Check for Action existence, then bind to function
	if(ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AMainPlayerController::HandleMove);
	}
	if(ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &AMainPlayerController::HandleLook);
	}
	if(ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &AMainPlayerController::HandleJump);
	}
	if(ActionCrouch)
	{
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, this, &AMainPlayerController::HandleCrouch);
	}
	if(ActionSprint)
	{
		EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Triggered, this, &AMainPlayerController::HandleSprint);
	}
}

void AMainPlayerController::OnUnPossess()
{
	//UnBind Inputs
	EnhancedInputComponent->ClearActionBindings();
	
	Super::OnUnPossess();
}

//MOVEMENT HANDLER FUNCTIONS
void AMainPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AMainPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
}

void AMainPlayerController::HandleJump()
{
	PlayerCharacter->UnCrouch();
	PlayerCharacter->Jump();
}

void AMainPlayerController::HandleCrouch()
{
	if(PlayerCharacter->bIsCrouched)
	{
		PlayerCharacter->UnCrouch();
	}
	else
	{
		PlayerCharacter->Crouch();
	}
}

void AMainPlayerController::HandleSprint()
{
	PlayerCharacter->ToggleRunning();
}
