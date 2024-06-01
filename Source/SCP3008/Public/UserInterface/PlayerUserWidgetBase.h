// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUserWidgetBase.generated.h"

/**
 * 
 */

USTRUCT()
struct FSomeStruct
{
	UPROPERTY(EditAnywhere)
	uint16 SomeValue = 0;

	GENERATED_BODY()
	
};

UCLASS(Abstract)
class SCP3008_API UPlayerUserWidgetBase : public UUserWidget
{
	

public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	UPROPERTY(EditAnywhere)
	uint16 SomeValue = 0;

protected:
private:
	GENERATED_BODY()
};
