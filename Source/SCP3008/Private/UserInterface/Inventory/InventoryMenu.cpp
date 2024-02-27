// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryMenu.h"
#include "Entities/MainPlayer.h"

void UInventoryMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UInventoryMenu::NativeConstruct()
{
    Super::NativeConstruct();

    Player = Cast<AMainPlayer>(GetOwningPlayerPawn());

}

bool UInventoryMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);


}
