// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/IkeaEmployee.h"

AIkeaEmployee::AIkeaEmployee()
{
	// PrimaryActorTick.bCanEverTick = true;
	//
	// ActorState = PATROL;
	//
	// setMarkovChain();
}

void ADefaultMob::Tick(float DeltaTime)
{
	// testing code below
	// SwitchState(ActorState, false);
	UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), ActorState);
	Super::Tick(DeltaTime);
	
}