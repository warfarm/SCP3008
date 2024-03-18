// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Components/InventoryComponent.h"

UItemBase::UItemBase() : bIsCopy(false), bIsPickUp(false)
{
    
}


void UItemBase::ResetItemFlags()
{
    bIsCopy = false;
    bIsPickUp = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
    UItemBase* ItemCopy{ NewObject<UItemBase>(StaticClass()) };

    ItemCopy->ID = this->ID;
    ItemCopy->ItemQuality = this->ItemQuality;
    ItemCopy->ItemType = this->ItemType;
    ItemCopy->TextData = this->TextData;
    ItemCopy->NumericData = this->NumericData;
    ItemCopy->AssetData = this->AssetData;
    ItemCopy->bIsCopy = true;
    
    return ItemCopy;
}
