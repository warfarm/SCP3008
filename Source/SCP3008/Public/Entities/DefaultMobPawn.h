// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntitiesInterface.h"
#include "GameFramework/Pawn.h"
#include "DefaultMobPawn.generated.h"

UCLASS()
class SCP3008_API ADefaultMobPawn : public APawn, public IEntitiesInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultMobPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
