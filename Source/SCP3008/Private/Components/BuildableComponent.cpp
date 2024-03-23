// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildableComponent.h"

// Sets default values for this component's properties
UBuildableComponent::UBuildableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UBuildableComponent::PickUp(AMainPlayer* TargetPlayer)
{
	if (bIsHeld)
	{
		// handle invalid state
		return;
	}

	HoldingPlayer = TargetPlayer;

	bIsHeld = true;
	
}

void UBuildableComponent::PlaceDown()
{
	if (!bIsHeld)
	{
		// handle invalid state
		return;
	}

	
	
	bIsHeld = false;
	
}


// Called when the game starts
void UBuildableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuildableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsHeld)
	{
		
	}
}

