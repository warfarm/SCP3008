// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Faction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCP3008_API UFaction : public UActorComponent
{
	GENERATED_BODY()

public:
	int id;
	FColor color;
	std::string name;
	
	
	



	// Sets default values for this component's properties
	UFaction();
	
	// Initialize the faction with an id, color, and name
	void Initailize(int32, FColor, std::string);


	// create an instance of the default faction associated with that id
	// 0 = Independent, 1 = SCP Foundation, 2 = Chaos Insurgency, 3 = Serpent's Hand
	static UFaction* createDefaultFaction(AActor*,int32);	
	// Generate unique id for custom factions
	static int32 generateId();

// Getters
	int32 getId() const;
	FColor getColor() const;
	std::string_view getName() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
