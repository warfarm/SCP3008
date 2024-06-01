// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class AMainCharacter;
class UMinimalLayoutBase;
class UBasicLayoutBase;
class UMaximumLayoutBase;
/**
 * 
 */

UENUM(BlueprintType)
enum class EHUDViewMode: uint8
{
	Clean UMETA(Tooltip="Clean, Basic HUD UI"),
	Minimal UMETA(Tooltip="Minimal, Basic Necessities"),
	Basic UMETA(Tooltip="Basic UI with necessities and additional features"),
	Maximum UMETA(Tooltip="Extravagance Galore!") 
};

UCLASS(Abstract)
class SCP3008_API APlayerHUD : public AHUD
{

public:
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UMinimalLayoutBase> MinimalLayoutClass = nullptr;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UBasicLayoutBase> BasicLayoutClass = nullptr;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UMaximumLayoutBase> MaximumLayoutClass = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetCurrentViewMode(EHUDViewMode NewViewMode);
	
	UFUNCTION(BlueprintCallable)
	void CycleToNextViewMode();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY(EditAnywhere)
	EHUDViewMode CurrentViewMode = EHUDViewMode::Basic;

	//Update Widgets
	void UpdateWidgets();

	//Clear binded Delegates
	void ClearAllHandlers();

	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;

	//UPROPERTY()
	//TObjectPtr<UMinimalLayoutBase> MinimalLayoutWidget = nullptr;

	//UPROPERTY()
	//TObjectPtr<UBasicLayoutBase> BasicLayoutWidget = nullptr;

	//UPROPERTY()
	//TObjectPtr<UMaximumLayoutBase> MaximumLayoutWidget = nullptr;

	//UPROPERTY()
	//TObjectPtr<AMainCharacter> PlayerCharacter = nullptr;

	GENERATED_BODY()
};
