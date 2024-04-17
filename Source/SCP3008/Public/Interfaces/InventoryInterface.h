// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <optional>

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

USTRUCT(Blueprintable)
struct FInventoryData
{
	GENERATED_BODY()

	FInventoryData() :
		InventoryTotalWeight(0),
		InventorySlotsCapacity(0),
		InventoryWeightCapacity(0){
	};
	
	FInventoryData(const int32 SlotCapacity, const int WeightCapacity, const std::optional<int32> SlotsToReserve) :
		InventoryTotalWeight(0),
		InventorySlotsCapacity(SlotCapacity),
		InventoryWeightCapacity(WeightCapacity)
	{
		InventoryContents.Reserve(SlotsToReserve.value_or(0));
	};
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventoryWeightCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Audio")
	USoundBase* PickUpSound = nullptr;
	
};
class UInventoryComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	
	GENERATED_BODY()
	// very important! (delete this)
	void VeryImportantFunction();
	
};

/**
 * 
 */
class SCP3008_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	
	UFUNCTION(Category = "Inventory")
	virtual UItemBase* FindMatchingItem(UItemBase* ItemIn) const;

	UFUNCTION(Category = "Inventory")
	virtual UItemBase* FindNextItemByID(UItemBase* ItemIn) const;
	UFUNCTION(Category = "Inventory")
	virtual FItemAddResult HandleAddItem(UItemBase* InputItem);
	UFUNCTION(Category = "Inventory")
	virtual void RemoveSingleInstance(UItemBase* ItemToRemove);

	UFUNCTION(Category = "Inventory")
	virtual void TransferItemInventory(UItemBase* ItemIn, UInventoryComponent* InventoryFrom, UInventoryComponent* InventoryTo);
	
	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE float GetInventoryTotalWeight() const {return InventoryData.InventoryTotalWeight;}
	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE float GetWeightCapacity() const {return InventoryData.InventoryWeightCapacity;}
	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE int32 GetSlotsCapacity() const {return InventoryData.InventorySlotsCapacity;}
	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryData.InventoryContents;}

	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE void SetTotalWeight(const int32 WeightToSet) {InventoryData.InventoryTotalWeight = WeightToSet;}
	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) {InventoryData.InventorySlotsCapacity = NewSlotsCapacity;}
	UFUNCTION(Category = "Inventory")
	virtual FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) {InventoryData.InventoryWeightCapacity = NewWeightCapacity;}
	
protected:
	FInventoryData InventoryData;
	virtual void AddNewItem(UItemBase* Item);
	
	int32 CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount);
};