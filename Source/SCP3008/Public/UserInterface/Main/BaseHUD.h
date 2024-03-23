// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

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

	bool bIsMenuVisible;

	ABaseHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY()
	UInventoryMenu* InventoryMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	virtual void BeginPlay() override;

};
