// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/PlayerUserWidgetBase.h"
#include "StatusHUDBase.generated.h"

class UStatusBarBase;
/**
 * 
 */
UCLASS(Abstract)
class SCP3008_API UStatusHUDBase : public UPlayerUserWidgetBase
{
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UStatusBarBase> HealthBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UStatusBarBase> StaminaBar = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UStatusBarBase> HungerBar = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UStatusBarBase> ThirstBar = nullptr;
	
	GENERATED_BODY()
	
};
