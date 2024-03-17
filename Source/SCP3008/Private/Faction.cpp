// Fill out your copyright notice in the Description page of Project Settings.


#include "Faction.h"

// Sets default values for this component's properties
UFaction::UFaction()
{

	
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UFaction::Initailize(int32 tid, FColor tcolor, std::string tname)
{
	this->id = tid;
	this->color = tcolor;
	this->name = tname;
}

// Called when the game starts
void UFaction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFaction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UFaction* UFaction::createDefaultFaction(AActor* Owner, int32 id)
{
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("UFaction::createDefaultFaction: Owner is null."));
		return nullptr;
	}

	UFaction* NewFaction = nullptr;

	switch (id)
	{
	case 0:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("Independent"));
		NewFaction->Initailize(0, FColor::White, "Independent");
		break;
	case 1:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("SCPFoundation"));
		NewFaction->Initailize(1, FColor::Blue, "SCP Foundation");
		break;
	case 2:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("ChaosInsurgency"));
		NewFaction->Initailize(2, FColor::Red, "Chaos Insurgency");
		break;
	case 3:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("SerpentsHand"));
		NewFaction->Initailize(3, FColor::Green, "Serpent's Hand");
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UFaction::createDefaultFaction: Invalid ID."));
		return nullptr;
	}
	
	return NewFaction;
}


int32 UFaction::generateId()
{
	static int32 id = 4;
	return id++;
}