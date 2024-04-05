// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdate);

class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item Added"),
	IAR_ItemAdded UMETA(DisplayName = "Item Added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult():
	AmountAdded(0),
	OperationResult(EItemAddResult::IAR_NoItemAdded),
	ResultMessage(FText::GetEmpty())
	{};
	
	//Added Amount? Maybe wont be used
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 AmountAdded;
	//Item Operation state Enum
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;
	//Operation Result Status Message
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult{};
		AddedNoneResult.AmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		return AddedNoneResult;
	};
	static FItemAddResult AddedAll(const FText& Message)
	{
		FItemAddResult AddedAllResult{};
		AddedAllResult.AmountAdded = 1;
		AddedAllResult.OperationResult = EItemAddResult::IAR_ItemAdded;
		AddedAllResult.ResultMessage = Message;
		return AddedAllResult;
	};

	bool operator == (const FItemAddResult& OtherAddResult) const
	{
		return this->OperationResult == OtherAddResult.OperationResult;
	}
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCP3008_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	FOnInventoryUpdate OnInventoryUpdate;

	UInventoryComponent();

	UFUNCTION(Category = "Inventory")
	UItemBase* FindMatchingItem(UItemBase* ItemIn) const;

	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextItemByID(UItemBase* ItemIn) const;
	UFUNCTION(Category = "Inventory")
	FItemAddResult HandleAddItem(UItemBase* InputItem);
	UFUNCTION(Category = "Inventory")
	void RemoveSingleInstance(UItemBase* ItemToRemove);

	UFUNCTION(Category = "Inventory")
	void TransferItemInventory(UItemBase* ItemIn, UInventoryComponent* InventoryFrom, UInventoryComponent* InventoryTo);
	
	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetInventoryTotalWeight() const {return InventoryTotalWeight;}
	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetWeightCapacity() const {return InventoryWeightCapacity;}
	UFUNCTION(Category = "Inventory")
	FORCEINLINE int32 GetSlotsCapacity() const {return InventorySlotsCapacity;}
	UFUNCTION(Category = "Inventory")
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents;}

	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetTotalWeight(const int32 WeightToSet) {InventoryTotalWeight = WeightToSet;}
	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) {InventorySlotsCapacity = NewSlotsCapacity;}
	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) {InventoryWeightCapacity = NewWeightCapacity;}
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventoryWeightCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	int32 CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount);

	void AddNewItem(UItemBase* Item);
	
};
