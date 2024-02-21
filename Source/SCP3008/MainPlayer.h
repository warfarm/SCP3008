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
	// Input stuff
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	class UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* JumpAction;

	// Camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
};
