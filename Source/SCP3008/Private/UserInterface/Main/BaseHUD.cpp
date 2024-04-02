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

	if (HotBarPanelWidget)
	{
		HotBarPanelWidget = CreateWidget<UHotBarPanel>(GetWorld(), HotBarPanelClass);
		HotBarPanelWidget->AddToViewport(-1);
		HotBarPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	if (InteractionWidget)
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
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABaseHUD::HideMenu()
{
	if (InventoryMenuWidget)
	{
		bIsMenuVisible = false;
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
		HotBarPanelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABaseHUD::HideHotBar()
{
	if(HotBarPanelWidget)
	{
		bIsMenuVisible = false;
		HotBarPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABaseHUD::ToggleHotBar()
{
	if (bIsHotBarVisible)
	{
		HideHotBar();
	}
	else
	{
		DisplayHotBar();
	}
}

void ABaseHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABaseHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InventoryMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
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

