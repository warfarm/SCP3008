// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Main/BaseHUD.h"
#include "UserInterface/Inventory/InventoryMenu.h"
#include "UserInterface/Interaction/InteractionWidget.h"
#include "UserInterface/Inventory/HotBarPanel.h"

ABaseHUD::ABaseHUD()
{
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	if (InventoryMenuClass)
	{
		InventoryMenuWidget = CreateWidget<UInventoryMenu>(GetWorld(), InventoryMenuClass);
		InventoryMenuWidget->AddToViewport(5);
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-2);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void ABaseHUD::DisplayMenu()
{
	if (InventoryMenuWidget)
	{
		bIsMenuVisible = true;
		bIsHotBarVisible = true;
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABaseHUD::HideMenu()
{
	if (InventoryMenuWidget)
	{
		bIsMenuVisible = false;
		bIsHotBarVisible = false;
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABaseHUD::ToggleMenu()
{
	if (bIsMenuVisible)
	{
		HideMenu();
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void ABaseHUD::DisplayHotBar()
{
	if(HotBarPanelWidget)
	{
		bIsMenuVisible = true;
		bIsHotBarVisible = true;
		HotBarPanelWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABaseHUD::HideHotBar()
{
	if(HotBarPanelWidget)
	{
		bIsHotBarVisible = false;
		bIsMenuVisible = false;
		HotBarPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABaseHUD::ToggleHotBar()
{

	UE_LOG(LogTemp, Warning, TEXT("ATTEMPTING TO TOGGLE HOTBAR"))
	if (bIsHotBarVisible)
	{
		HideHotBar();
		UE_LOG(LogTemp, Warning, TEXT("ATTEMPTING TO TOGGLE2 HOTBAR"))
	}
	else
	{
		DisplayHotBar();
		UE_LOG(LogTemp, Warning, TEXT("ATTEMPTING TO UNTOGGLE HOTBAR"))
	}
}

void ABaseHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABaseHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABaseHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		

		InteractionWidget->UpdateWidget(InteractableData);
		
	}
}

