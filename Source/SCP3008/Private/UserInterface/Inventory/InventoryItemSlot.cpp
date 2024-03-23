// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/InventoryTooltip.h"

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemReference)
	{
		switch(ItemReference->ItemQuality) {
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(CommonColor);
			break;
		case EItemQuality::Uncommon:
			ItemBorder->SetBrushColor(UncommonColor);
			break;
		case EItemQuality::Rare:
			ItemBorder->SetBrushColor(RareColor);
			break;
		case EItemQuality::Prime:
			ItemBorder->SetBrushColor(PrimeColor);
			break;
		case EItemQuality::Special:
			ItemBorder->SetBrushColor(SpecialColor);
			break;
		case EItemQuality::Anomalous:
			ItemBorder->SetBrushColor(AnomalousColor);
			break;
		}

		ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
		
	}
}

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(ToolTipClass)
	{
		UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;
		SetToolTip(ToolTip);
	}
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}


void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

