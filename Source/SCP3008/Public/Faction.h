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
	UTexture2D* icon;
	
	
	



	// Sets default values for this component's properties
	UFaction();

	// Setters
	
	// Initialize the faction with an id, color, and name
	void Initailize(int32, FColor, std::string);
	// set the icon for the faction
	void setIcon(UTexture2D*);
	


	// create an instance of the default faction associated with that id
	// 0 = Independent, 1 = SCP Foundation, 2 = Chaos Insurgency, 3 = Serpent's Hand, 4 = UNGOC
	UFUNCTION(BlueprintCallable, Category = "Factions", meta = (DnvisplayName = "Create Default Faction"))
	static UFaction* CreateDefaultFaction(AActor* Owner, int32 id);	
	// Generate unique id for custom factions
	static int32 generateId();

// Getters
	int32 getId() const;
	FColor getColor() const;
	std::string_view getName() const;
	UTexture2D* getIcon() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Load the icon for a static faction
	static UTexture2D* loadIcon(int id);

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
