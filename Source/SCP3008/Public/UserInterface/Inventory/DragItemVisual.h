// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItemVisual.generated.h"

class UBorder;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SCP3008_API UDragItemVisual : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly,  Category = "DragItem Visual", meta = (BindWidget))
	UBorder* ItemBorder{};

	UPROPERTY(EditDefaultsOnly,  Category = "DragItem Visual", meta = (BindWidget))
	UImage* ItemIcon{};
};
