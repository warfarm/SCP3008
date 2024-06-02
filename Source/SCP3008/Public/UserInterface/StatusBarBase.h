// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/PlayerUserWidgetBase.h"
#include "Brushes/SlateColorBrush.h"
#include "StatusBarBase.generated.h"

/**
 * 
 */

class UHorizontalBox;
class UBorder;
class UImage;
class UTextBlock;

UCLASS(Abstract)
class SCP3008_API UStatusBarBase : public UPlayerUserWidgetBase
{

public:

	//OnIntStatusUpdate
	UFUNCTION()
	void OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue);

	//OnFloatStatusUpdate
	UFUNCTION()
	void OnFloatStatUpdated(float OldValue, float NewValue, float MaxValue);

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHorizontalBox> PercentBars = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UImage> IconImage = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> PercentBar_Filled = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> PercentBar_Empty = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UTextBlock> ValueText = nullptr;

private:
	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FSlateBrush IconBrush;

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor BarBackgroundColor = FLinearColor(0.3f, 0.0f, 0.0f, 0.3f);

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor BarForegroundColor = FLinearColor(1.0f, 0.0f, 0.0f, 0.7f);

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	bool IsFullSize = true;

	UPROPERTY(EditAnywhere, Category="Stat Bar | Testing", meta=(ClampMin=0, UIMin=0, ClampMax=1, UIMax=1, Units="Percent"))
	float CurrentPercentage = 0.0f;

	UPROPERTY(EditAnywhere, Category="Stat Bar | Testing", meta=(ClampMin=0, UIMin=0))
	float CurrentValue = 100.0f;

	FText CurrentValueText;

	void ProcessCurrentValueText();

	void UpdateWidget();
	
	GENERATED_BODY()
	
};
