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

UFaction* UFaction::CreateDefaultFaction(AActor* Owner, int32 id)
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
		NewFaction->setIcon(loadIcon(0));
		break;
	case 1:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("SCPFoundation"));
		NewFaction->Initailize(1, FColor::Blue, "SCP Foundation");
		NewFaction->setIcon(loadIcon(1));
		break;
	case 2:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("ChaosInsurgency"));
		NewFaction->Initailize(2, FColor::Red, "Chaos Insurgency");
		NewFaction->setIcon(loadIcon(2));
		break;
	case 3:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("SerpentsHand"));
		NewFaction->Initailize(3, FColor::Green, "Serpent's Hand");
		NewFaction->setIcon(loadIcon(3));
		break;
	case 4:
		NewFaction = Owner->CreateDefaultSubobject<UFaction>(TEXT("UNGOC"));
		NewFaction->Initailize(4, FColor::Yellow, "United Nations Global Occult Coalition");
		NewFaction->setIcon(loadIcon(4));
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UFaction::createDefaultFaction: Invalid ID."));
		return nullptr;
	}
	
	return NewFaction;
}

// Load the Image for a static faction
UTexture2D* UFaction::loadIcon(int fid)
{
	std::string basePath = "Game/FactionIcons/";
	switch (fid)
	{
	case 1:
		basePath += "FI_SCPFoundation";
		break;
	case 2:
		basePath += "FI_ChaosInsurgency";
		break;
	case 3:
		basePath += "FI_SerpentsHand";
		break;
	case 4:
		basePath += "FI_UNGOC";
		break;
	default:
		basePath += "FI_Independent";
		break;
	}
	basePath += ".png";
	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FString(basePath.c_str())));
	
	
}


// Load the icon for the faction
void UFaction::setIcon(UTexture2D* ficon)
{
	this->icon = ficon;
}


int32 UFaction::generateId()
{
	static int32 id = 4;
	return id++;
}