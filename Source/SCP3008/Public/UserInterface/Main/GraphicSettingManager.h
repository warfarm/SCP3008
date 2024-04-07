// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GraphicSettingManager.generated.h"


class UComboBoxString;
class UCheckBox;
/**
 * 
 */
UCLASS()
class SCP3008_API UGraphicSettingManager : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

protected:
	void InitializeResolutionComboBox();
	void InitializeVSync();
	void InitializeGraphicQuality();

	UFUNCTION()
	void OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType);

	UFUNCTION()
	void OnVSyncChanged(bool InIsChecked);

	UFUNCTION()
	void OnGraphicSettingChanged(int InSelectedItem, ESelectInfo::Type InSelectionType);

	UPROPERTY()
	TObjectPtr<UGameUserSettings> GameUserSettings;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UComboBoxString> ResolutionComboBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCheckBox> VSyncCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UComboBoxString> GraphicSettingComboBox;

	UPROPERTY()
	TArray<FIntPoint> Resolutions;

	UPROPERTY()
	TArray<int> GraphicSettings;


};
