// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildableComponent.h"

#include "Entities/MainPlayer.h"

// Sets default values for this component's properties
UBuildableComponent::UBuildableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// TODO! 
void UBuildableComponent::PickUp(AMainPlayer* TargetPlayer)
{
	if (bIsHeld)
	{
		// handle invalid state
		return;
	}

	HoldingPlayer = TargetPlayer;

	bIsHeld = true;

	StaticMesh->SetSimulatePhysics(false);
	GetOwner()->SetActorEnableCollision(false);
}

void UBuildableComponent::PlaceDown()
{
	if (!bIsHeld)
	{
		// handle invalid state
		return;
	}

	bIsHeld = false;

	// TODO! do more checks if in wall etc etc
	StaticMesh->SetSimulatePhysics(true);
	GetOwner()->SetActorEnableCollision(true);
}

// TODO! trigger w scrolling while in build mode
void UBuildableComponent::ShiftOffset(float Distance)
{
	OffsetFromPlayer = FMath::Clamp(OffsetFromPlayer + Distance, 100, 400);
	
}


// Called when the game starts
void UBuildableComponent::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh = CastChecked<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

}


// Called every frame
void UBuildableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsHeld)
	{
		AActor* Owner = GetOwner();

		// TODO! 
		Owner->SetActorLocation(HoldingPlayer->GetCameraPosition() + HoldingPlayer->GetLookVector() * OffsetFromPlayer);
	}
}

