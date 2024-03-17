// Fill out your copyright notice in the Description page of Project Settings.


// #include "DefaultMobController.h"
#include "Entities/DefaultMobController.h"

// define the static variables
 TArray<TArray<float>> ADefaultMobController::markovMatrix { {0.9f, 0.1f}, {0.1f, 0.9f} };

// Sets default values
ADefaultMobController::ADefaultMobController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorState = PATROL;

	setMarkovChain();
	
	
}
void ADefaultMobController::setMarkovChain( )
{
	markovMatrix = { {0.9f, 0.1f}, {0.1f, 0.9f} };
	
}



// Called when the game starts or when spawned
void ADefaultMobController::BeginPlay()
{
	Super::BeginPlay();
	SwitchState();
	
}



// Called every frame 
void ADefaultMobController::Tick(float DeltaTime)
{
	// testing code below
	// SwitchState(ActorState, false);
	// UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), ActorState);
	Super::Tick(DeltaTime);
	
}


// calls switchstate with override
bool ADefaultMobController::ExitAlways()
{
	
	SwitchState(true);

	return true;
}
// calls switchstate with no override
bool ADefaultMobController::ExitSafe()
{
	
	SwitchState();
	return true;
}
void ADefaultMobController::Stun(float duration)
{
	OnStun(duration);
	ActorState = STUNNED;
}



// bOvveride default value set in header file
void ADefaultMobController::SwitchState(bool bOverride)
{
	float random = FMath::FRand();
	if (ActorState == PATROL)
	{
		
		if (random < markovMatrix[0][1])
		{
			ActorState = IDLE;
			// Idle();
		}
	}
	else if (ActorState == IDLE)
	{
		
		if (random < markovMatrix[1][0])
		{
			ActorState = PATROL;
		}
	}
	else if (bOverride)
	{
		
		if (random < markovMatrix[0][1])
		{
			ActorState = IDLE;
		}
		else
		{
			ActorState = PATROL;
		}
	}
	// Testing code below
	
	
}


