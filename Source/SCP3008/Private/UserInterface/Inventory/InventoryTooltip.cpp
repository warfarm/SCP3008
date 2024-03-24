// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryTooltip.h"

// #include "IDetailTreeNode.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Items/ItemBase.h"

void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();

	switch (ItemBeingHovered->ItemType)
	{
	case EItemType::Consumable:
		ItemType->SetText(FText::FromString("Consumable"));
		UsageText->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Tool:
		ItemType->SetText(FText::FromString("Tool"));
		UsageText->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Armor:
		ItemType->SetText(FText::FromString("Armor"));
		UsageText->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Weapon:
		ItemType->SetText(FText::FromString("Weapon"));
		UsageText->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Item:
		ItemType->SetText(FText::FromString("Item"));
		UsageText->SetVisibility(ESlateVisibility::Visible);
		break;
	}

	ItemName->SetText(ItemBeingHovered->TextData.Name);
	UsageText->SetText(ItemBeingHovered->TextData.UsageText);
	ItemDescription->SetText(ItemBeingHovered->TextData.Description);
	ItemWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemWeight()));

	
}