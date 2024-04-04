// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Items/ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
	if(ItemIn)
	{
		if(InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	if(ItemIn)
	{
		if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	if (GetOwner())
	{
		
		//Check Weight Overflow
		if (FMath::IsNearlyZero(InputItem->GetItemWeight()) || InputItem->GetItemWeight() < 0)
		{
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Could not add {0} to inventory. Item has invalid Weight Value."),
				InputItem->TextData.Name));
		}

		//Check Weight Overflow
		if (InventoryTotalWeight + InputItem->GetItemWeight() > GetWeightCapacity())
		{
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Could not add {0} to inventory. Item would exceed weight limit."),
				InputItem->TextData.Name));
		}

		//Check Slot Overflow
		if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
		{
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Could not add {0} to inventory. Item would exceed slot limit."),
				InputItem->TextData.Name));
		}

		AddNewItem(InputItem);
		return FItemAddResult::AddedAll(FText::Format(
				FText::FromString("Successfully added {0} to Inventory."),
				InputItem->TextData.Name));
	}

	AddNewItem(InputItem);
	
	return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Added nothing, owner not found."),
				InputItem->TextData.Name));
}

void UInventoryComponent::RemoveSingleInstance(UItemBase* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);
	int32 WeightToSet = FMath::FloorToInt32((this->GetInventoryTotalWeight()) - (ItemToRemove->NumericData.Weight));
	if(WeightToSet <= 0)
	{
		WeightToSet = 0;
	}
	this->SetTotalWeight(WeightToSet);
	OnInventoryUpdate.Broadcast();
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt32((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetItemWeight());
	if(WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

void UInventoryComponent::TransferItemInventory(UItemBase* ItemIn, UInventoryComponent* InventoryFrom, UInventoryComponent* InventoryTo)
{
	if(InventoryFrom && InventoryTo)
	{
		//Remove Item from InventoryFrom
		//AddNewItem in InventoryTo
	}
}


void UInventoryComponent::AddNewItem(UItemBase* Item)
{
	UItemBase* NewItem{};

	//Pointer!!!
	if(Item->bIsCopy || Item->bIsPickUp)
	{
		//Check If Item is already Copy or Pickup Actor
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwnedInventory = this;

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemWeight();
	OnInventoryUpdate.Broadcast();
}