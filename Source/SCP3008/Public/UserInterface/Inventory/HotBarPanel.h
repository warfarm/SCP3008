// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotBarPanel.generated.h"

class UInventoryItemSlot;
class UInventoryComponent;
class AMainPlayer;
class UWrapBox;
/**
 * 
 */
UCLASS()
class SCP3008_API UHotBarPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void RefreshHotBar();

	UPROPERTY(meta=(BindWidget))
	UWrapBox* HotBarPanel;

	UPROPERTY(meta=(BindWidget))
	UInventoryItemSlot* SlotOne;
	
	UPROPERTY(meta=(BindWidget))
	UInventoryItemSlot* SlotTwo;
	
	UPROPERTY(meta=(BindWidget))
	UInventoryItemSlot* SlotThree;
	
	UPROPERTY(meta=(BindWidget))
	UInventoryItemSlot* SlotFour;
	
	UPROPERTY()
	AMainPlayer* Player;

	UPROPERTY()
	UInventoryComponent* HotBarReference;
	
};
