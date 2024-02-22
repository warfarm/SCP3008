// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EntitiesInterface.generated.h"

USTRUCT()
struct FEntitiesData
{
	GENERATED_USTRUCT_BODY()

	FEntitiesData() = default;

	UPROPERTY(EditInstanceOnly)
	float Health{};

	UPROPERTY(EditInstanceOnly)
	float Speed{};

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* EntityMesh{};
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEntitiesInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCP3008_API IEntitiesInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FEntitiesData EntityData;
};
