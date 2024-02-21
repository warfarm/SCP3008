// Fill out your copyright notice in the Description page of Project Settings.


#include "IkeaEmployee.h"

// define the static variables
TArray<TArray<float>> AIkeaEmployee::markovMatrix { {0.9f, 0.1f}, {0.1f, 0.9f} };

// Sets default values
AIkeaEmployee::AIkeaEmployee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorState = PATROL;

	
	
}

// Called when the game starts or when spawned
void AIkeaEmployee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIkeaEmployee::Tick(float DeltaTime)
{
	// testing code below
	// SwitchState(ActorState, false);
	// UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), ActorState);
	Super::Tick(DeltaTime);
	
}

void AIkeaEmployee::SwitchState(EnemyState& currentState, bool bOverride)
{
	float random = FMath::FRand();
	if (currentState == PATROL)
	{
		
		if (random < markovMatrix[0][1])
		{
			currentState = IDLE;
		}
	}
	else if (currentState == IDLE)
	{
		
		if (random < markovMatrix[1][0])
		{
			currentState = PATROL;
		}
	}
	else if (bOverride)
	{
		
		if (random < markovMatrix[0][1])
		{
			currentState = IDLE;
		}
		else
		{
			currentState = PATROL;
		}
	}
	// Testing code below
	
	
}


