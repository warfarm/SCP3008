// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Prime UMETA(DisplayName = "Prime"),
	Special UMETA(DisplayName = "Special"),
	Anomalous UMETA(DisplayName = "Anomalous"),
};

UENUM()
enum class EItemType : uint8
{
	Consumable UMETA(DisplayName = "Consumable"),
	Tool UMETA(DisplayName = "Tool"),
	Armor UMETA(DisplayName = "Armor"),
	Weapon UMETA(DisplayName = "Weapon"),
	Item UMETA(DisplayName = "Item"),
};

USTRUCT()
struct FItemTextData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name{};

	UPROPERTY(EditAnywhere)
	FText Description{};

	UPROPERTY(EditAnywhere)
	FText InteractionText{};

	UPROPERTY(EditAnywhere)
	FText UsageText{};

};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float Weight{};
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon{};

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh{};
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

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
};