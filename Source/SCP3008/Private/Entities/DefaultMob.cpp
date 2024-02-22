// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\Entities\DefaultMob.h"

// define the static variables
 TArray<TArray<float>> ADefaultMob::markovMatrix { {0.9f, 0.1f}, {0.1f, 0.9f} };

// Sets default values
ADefaultMob::ADefaultMob()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorState = PATROL;

	
	
}
void ADefaultMob::setMarkovChain(TArray<TArray<float>> newChain )
{
	markovMatrix = newChain;
	
}



// Called when the game starts or when spawned
void ADefaultMob::BeginPlay()
{
	Super::BeginPlay();
	SwitchState();
	
}



// Called every frame 
void ADefaultMob::Tick(float DeltaTime)
{
	// testing code below
	// SwitchState(ActorState, false);
	// UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), ActorState);
	Super::Tick(DeltaTime);
	
}
void ADefaultMob::Idle()
{
	
	ActorState = IDLE;
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ADefaultMob::ExitSafe, 5.0f, false);
}
void ADefaultMob::Stun(float duration)
{
	ActorState = STUNNED;
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ADefaultMob::ExitAlways, duration, false);
}



void ADefaultMob::ExitAlways()
{
	UE_LOG(LogTemp, Warning, TEXT("FunctionCalled"));
	SwitchState(true);
}
void ADefaultMob::ExitSafe()
{
	
	SwitchState();
}

// bOvveride default value set in header file
void ADefaultMob::SwitchState(bool bOverride)
{
	float random = FMath::FRand();
	if (ActorState == PATROL)
	{
		
		if (random < markovMatrix[0][1])
		{
			ActorState = IDLE;
			Idle();
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


