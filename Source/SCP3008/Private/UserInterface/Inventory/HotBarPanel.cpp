// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/HotBarPanel.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Components/InventoryComponent.h"
#include "Entities/MainPlayer.h"

#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

void UHotBarPanel::RefreshHotBar()
{
	if(HotBarReference && HotBarSlotClass)
	{
		HotBarPanel->ClearChildren();
		for(UItemBase* const& InventoryItem : HotBarReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, HotBarSlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			//HotBarPanel->AddChildToWrapBox(ItemSlot);
		}
		SetInfoText();
	}
}

void UHotBarPanel::SetInfoText() const
{
	const FString WeightInfoValue{
		FString::SanitizeFloat(HotBarReference->GetInventoryTotalWeight())
		+ "/"
		+ FString::SanitizeFloat(HotBarReference->GetWeightCapacity())
	};

	HotBarWeightInfo->SetText(FText::FromString(WeightInfoValue));
}

void UHotBarPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AMainPlayer>(GetOwningPlayerPawn());
	if(Player)
	{
		HotBarReference = Player->GetHotBar();
		if (HotBarReference)
		{
			HotBarReference->OnInventoryUpdate.AddUObject(this, &UHotBarPanel::RefreshHotBar);
			SetInfoText();
		}
	}
}

bool UHotBarPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if(ItemDragDrop->SourceItem && HotBarReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected Item Drop on HotBar"));

		HotBarReference->TransferItemInventory(ItemDragDrop->SourceItem, ItemDragDrop->SourceInventory, HotBarReference);
		
		return true;
	}
	return false;
}
