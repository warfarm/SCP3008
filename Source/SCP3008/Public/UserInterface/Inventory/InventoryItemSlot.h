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
	FLinearColor CommonColor	= FLinearColor(FColor(222,	222, 222, 1));	// Grey
	FLinearColor UncommonColor	= FLinearColor(FColor(94,	231, 136, 1));	// Green
	FLinearColor RareColor		= FLinearColor(FColor(94,	121, 231, 1));	// Blue
	FLinearColor PrimeColor		= FLinearColor(FColor(238,	241,	39, 1));	// Yellow
	FLinearColor SpecialColor	= FLinearColor(FColor(155,	94,	231, 1));	// Purple
	FLinearColor AnomalousColor	= FLinearColor(FColor(231,	94,	102, 1));	// Red
	
	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	TSubclassOf<UDragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot")
	TSubclassOf<UInventoryTooltip> ToolTipClass;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UItemBase* ItemReference;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot", meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(EditDefaultsOnly,  Category = "Inventory Slot", meta = (BindWidget))
	UImage* ItemIcon;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
