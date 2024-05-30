// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
class AMainCharacter;
/**
 * 
 */
UCLASS(Abstract)
class SCP3008_API AMainPlayerController : public APlayerController
{
protected:
	//Multipliers
	float SprintMultiplier = 2.0f;
	
	//Native On Pawn posses and unPosses functions
	virtual void OnPossess(APawn* APawn) override;
	virtual void OnUnPossess() override;

	//Handler Functions
	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandleCrouch();
	void HandleSprint();

public:
	//Declare InputActions to be set later in Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionSprint = nullptr;
	
	//Reference for InputMappingContexts
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContent = nullptr;
	
private:
	//Store Reference to InputComponent
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	//Store Player Pawn/Character
	UPROPERTY()
	AMainCharacter* PlayerCharacter = nullptr;
	
	GENERATED_BODY()
};
