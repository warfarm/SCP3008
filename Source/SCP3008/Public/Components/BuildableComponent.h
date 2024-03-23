// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "BuildableComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCP3008_API UBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	/* ----- ATTRIBUTES ----- */
	FRotator3d SavedRotation{};
	bool bIsHeld{false};
	AMainPlayer* HoldingPlayer;

	// this will be set dynamically
	float PlayerOffset{};
	
	/* ----- ENGINE OVERRIDES ----- */
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UBuildableComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// erm akshaully you could just implememnt the UII interface and override the virtual methods 
	// TODO! make this shit return a Result<T, E> type
	virtual void PickUp(AMainPlayer* TargetPlayer);
	virtual void PlaceDown();

};
