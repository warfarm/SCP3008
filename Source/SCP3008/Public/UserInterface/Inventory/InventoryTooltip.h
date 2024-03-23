// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UTextBlock;
class UInventoryItemSlot;
/**
 * 
 */
UCLASS()
class SCP3008_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	UInventoryItemSlot* InventorySlotBeingHovered;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemWeight;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* UsageText;
protected:
	virtual void NativeConstruct() override;
};
