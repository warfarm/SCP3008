// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/IkeaEmployeeController.h"

AIkeaEmployeeController::AIkeaEmployeeController()
{
	// PrimaryActorTick.bCanEverTick = true;
	//
	// ActorState = PATROL;
	//
	// setMarkovChain();
}

void AIkeaEmployeeController::Tick(float DeltaTime)
{
	// testing code below
	// SwitchState(ActorState, false);
	UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), ActorState);
	Super::Tick(DeltaTime);
	
}
void AIkeaEmployeeController::BeginPlay()
{
	Super::BeginPlay();
	
}