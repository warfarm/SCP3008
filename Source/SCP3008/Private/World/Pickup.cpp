// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Pickup.h"

#include "Items/ItemBase.h"

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass());
	
}

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetSimulatePhysics(true);
	SetRootComponent(PickupMesh);
	
}

void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);

		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->NumericData = ItemData->NumericData;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;

		PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
	}
}

void APickup::BeginFocus()
{
	if(PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus()
{
	if(PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(false);
	}
}

void APickup::Interact(AMainPlayer* Player)
{
	if (Player)
	{
		TakePickup(Player);
	}
}

void APickup::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReference->TextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->TextData.Name;
	
	InteractableData = InstanceInteractableData;
}


void APickup::TakePickup(const AMainPlayer* Taker)
{
	if(!IsPendingKillPending())
	{
		if(ItemReference)
		{
			
		}
	}
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if(ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID))
	{
		if(ItemDataTable)
		{
			if(const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
			}
		}
	}
}

void APickup::InitializeDrop(UItemBase* ItemToDrop)
{
	ItemReference = ItemToDrop;
	ItemReference->NumericData.Weight = ItemToDrop->GetItemWeight();
	PickupMesh->SetStaticMesh(ItemToDrop->AssetData.Mesh);
	UpdateInteractableData();
}


