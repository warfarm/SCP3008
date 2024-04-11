// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/IkeaEmployeeController.h"

#include "Kismet/GameplayStatics.h"

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
	GetWorldTimerManager().SetTimer(voiceLineTimerHandle, this, &AIkeaEmployeeController::PlayRandomVoiceLine,
		voiceLineFrequency, true);
}

void AIkeaEmployeeController::PlayRandomVoiceLine()
{
	srand(time(0));
	int index = std::rand() % 3;
	UGameplayStatics::PlaySoundAtLocation(this, voiceLines[index], GetOwner()->GetActorLocation());
	
}
