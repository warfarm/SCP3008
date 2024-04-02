// Fill out your copyright notice in the Description page of Project Settings.
#include "UserInterface/Inventory/InventoryPanel.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/HotBarPanel.h"
#include "Components/InventoryComponent.h"
#include "Entities/MainPlayer.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

void UInventoryPanel::RefreshInventory()
{
	if(InventoryReference && InventorySlotClass)
	{
		InventoryPanel->ClearChildren();
		for(UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}
		SetInfoText();
	}
}

void UInventoryPanel::SetInfoText() const
{
	const FString WeightInfoValue{
		FString::SanitizeFloat(InventoryReference->GetInventoryTotalWeight())
		+ "/"
		+ FString::SanitizeFloat(InventoryReference->GetWeightCapacity())
	};
	
	const FString CapacityInfoValue{
		FString::SanitizeFloat(InventoryReference->GetInventoryContents().Num())
		+ "/"
		+ FString::SanitizeFloat(InventoryReference->GetSlotsCapacity())
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

void UInventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AMainPlayer>(GetOwningPlayerPawn());
	if(Player)
	{
		InventoryReference = Player->GetInventory();
		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdate.AddUObject(this, &UInventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if(ItemDragDrop->SourceItem && InventoryReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected Item Drop on Inventory Panel"));
		return true;
	}
	if(ItemDragDrop->SourceItem && Player->GetHotBar())
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected Item Drop on HotBar Panel"));
		return true;
	}
	return false;
}
