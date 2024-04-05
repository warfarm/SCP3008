// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotBarPanel.generated.h"

class UTextBlock;
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
	UTextBlock* HotBarWeightInfo;
	
	UPROPERTY()
	AMainPlayer* Player;

	UPROPERTY()
	UInventoryComponent* HotBarReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryItemSlot> HotBarSlotClass;
	
protected:
	void SetInfoText() const;
	
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
