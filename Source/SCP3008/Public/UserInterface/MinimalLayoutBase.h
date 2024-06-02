// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/PlayerUserWidgetBase.h"
#include "MinimalLayoutBase.generated.h"

class UStatusHUDBase;

/**
 * 
 */

UCLASS()
class SCP3008_API UMinimalLayoutBase : public UPlayerUserWidgetBase
{
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UStatusHUDBase> StatusHUDBase = nullptr;
	
	GENERATED_BODY()
};
