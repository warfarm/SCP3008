// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InventoryInterface.h"

#include "Components/InventoryComponent.h"

// Add default functionality here for any IInventoryInterface functions that are not pure virtual.

UItemBase* IInventoryInterface::FindMatchingItem(UItemBase* ItemIn) const
{
	return ItemIn;
}

UItemBase* IInventoryInterface::FindNextItemByID(UItemBase* ItemIn) const
{
	return ItemIn;
}

FItemAddResult IInventoryInterface::HandleAddItem(UItemBase* InputItem)
{
	return FItemAddResult::AddedNone(FText::GetEmpty());
}

void IInventoryInterface::RemoveSingleInstance(UItemBase* ItemToRemove)
{
}

void IInventoryInterface::TransferItemInventory(UItemBase* ItemIn, UInventoryComponent* InventoryFrom,
	UInventoryComponent* InventoryTo)
{
}

void IInventoryInterface::AddNewItem(UItemBase* Item)
{
}

int32 IInventoryInterface::CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	return 0;
}
	