// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UHotBarPanel;
struct FInteractableData;
class UInventoryMenu;
class UInteractionWidget;

UCLASS()
class SCP3008_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInventoryMenu> InventoryMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UHotBarPanel> HotBarPanelClass;
	
	bool bIsMenuVisible;
	bool bIsHotBarVisible;

	ABaseHUD();

	// Inventory Menu Toggles
	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	// HotBar Menu Toggles
	void DisplayHotBar();
	void HideHotBar();
	void ToggleHotBar();

	// Interactions Toggles
	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY()
	UInventoryMenu* InventoryMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UHotBarPanel* HotBarPanelWidget;
	
	virtual void BeginPlay() override;

};
