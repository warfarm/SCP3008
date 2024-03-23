// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemSlot.generated.h"

class UImage;
class UTextBlock;
class UBorder;
class UInventoryTooltip;
class UDragItemVisual;
class UItemBase;
/**
 * 
 */
UCLASS()
class UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()


public:
	FORCEINLINE void SetItemReference(UItemBase* ItemIn){ ItemReference = ItemIn;}
	FORCEINLINE UItemBase* GetItemReference() const {return ItemReference; }
protected:

	// FLinear Color (R, G, B, a) Red, Blue, Green, alpha [LEAVE ALPHA AT 1 IF NOT SURE]
	FLinearColor CommonColor	= FLinearColor(222.0f,	222.0f, 222.0f, 1.0f);	// Grey
	FLinearColor UncommonColor	= FLinearColor(94.0f,	231.0f, 136.0f, 1.0f);	// Green
	FLinearColor RareColor		= FLinearColor(94.0f,	121.0f, 231.0f, 1.0f);	// Blue
	FLinearColor PrimeColor		= FLinearColor(238.0f,	241.0f,	39.0f, 1.0f);	// Yellow
	FLinearColor SpecialColor	= FLinearColor(155.0f,	94.0f,	231.0f, 1.0f);	// Purple
	FLinearColor AnomalousColor	= FLinearColor(231.0f,	94.0f,	102.0f, 1.0f);	// Red
	
	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	TSubclassOf<UDragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	TSubclassOf<UInventoryTooltip> ToolTipClass;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UItemBase* ItemReference;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	UBorder* ItemBorder;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	UImage* ItemIcon;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	UTextBlock* ItemQuality;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
