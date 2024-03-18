// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

class UInventoryComponent;

UCLASS()
class SCP3008_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	UInventoryComponent* OwnedInventory;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID{};

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType{};

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality{};

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData TextData{};

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData NumericData{};

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData AssetData{};

	bool bIsCopy{};
	bool bIsPickUp{};
	
	UItemBase();

	void ResetItemFlags();
	
	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemWeight() const { return NumericData.Weight; };
	
	//UFUNCTION(Category = "Item")
	//virtual void Use(AMainPlayer* Player);

protected:

	bool operator == (const FName& OtherID) const
	{
		return this->ID == OtherID;
	}

};