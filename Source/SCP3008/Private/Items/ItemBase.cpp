// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

UItemBase* UItemBase::CreateItemCopy() const
{
    UItemBase* ItemCopy{ NewObject<UItemBase>(StaticClass()) };

    ItemCopy->ID = this->ID;
    ItemCopy->ItemQuality = this->ItemQuality;
    ItemCopy->ItemType = this->ItemType;
    ItemCopy->TextData = this->TextData;
    ItemCopy->NumericData = this->NumericData;
    ItemCopy->AssetData = this->AssetData;

    return ItemCopy;
}

//void UItemBase::Use(AMainPlayer* Player)
//{
//}
