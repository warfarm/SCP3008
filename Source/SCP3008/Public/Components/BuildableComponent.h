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
	float OffsetFromPlayer{};

	// subject to change later
	float MinOffset{ 200 };
	float MaxOffset{ 900 };
	
	AMainPlayer* HoldingPlayer;
	UStaticMeshComponent* StaticMesh;
	
	/* ----- ENGINE OVERRIDES ----- */
	// Called when the game starts
	virtual void BeginPlay() override;

	/* ----- UTILITY ----- */
	bool CollidesWithValidComponent();

public:	
	// Sets default values for this component's properties
	UBuildableComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// erm akshaully you could just implememnt the UII interface and override the virtual methods 
	// TODO! make this shit return a Result<T, E> type
	void PickUp(AMainPlayer* TargetPlayer);
	void PlaceDown();

	// Capped at 100 and 900. subject to change later perahsp?
	void ShiftOffsetFlat(float Distance);
	void ShiftOffsetPercent(float PercentChange);

};
