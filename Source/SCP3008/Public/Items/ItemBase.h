// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class SCP3008_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData{};

	UItemBase() = default;

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy();

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemWeight() const { return NumericData.Weight; };

	//UFUNCTION(Category = "Item")
	//virtual void Use(AMainPlayer* Player);

protected:

	bool operator == (const FName& OtherID) const
	{
		return ID == OtherID;
	}

};
