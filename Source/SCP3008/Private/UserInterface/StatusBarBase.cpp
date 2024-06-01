// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/StatusBarBase.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UStatusBarBase::OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue)
{
	OnFloatStatUpdated(static_cast<float>(OldValue), static_cast<float>(NewValue), static_cast<float>(MaxValue));
}

void UStatusBarBase::OnFloatStatUpdated(float OldValue, float NewValue, float MaxValue)
{
	if(MaxValue == 0.0f)
	{
		MaxValue = KINDA_SMALL_NUMBER; //KINDA_SMALL_NUMBER is official Epic Code; used here to prevent division by 0
	}
	CurrentPercentage = FMath::Clamp(NewValue/MaxValue, 0.0f, 1.0f);
	CurrentValue = NewValue;
	UpdateWidget();
}
#if WITH_EDITOR
void UStatusBarBase::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
	Super::OnDesignerChanged(EventArgs);
	UpdateWidget();
}

void UStatusBarBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateWidget();
}
#endif
void UStatusBarBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UpdateWidget();
}

void UStatusBarBase::ProcessCurrentValueText()
{
	//TEMPORARY PARSER, REWRITE LATER!!!
	
	//If the number is <10 then display it as a float to 2DP : 0.01
	//If the number is <100, then display it as a float with 1DP : 99.9
	//If the number is <1000 then display it as an integer with 0DP: 986
	//If the number is >= 1000, then divide it by 1000 and apply the rules above, and add a 'k' on the end
	
	FString FloatString;

	if(CurrentValue < 1000.0f)
	{
		FloatString = FString::SanitizeFloat(CurrentValue);

		if(CurrentValue < 100.0f)
		{
			int32 StringLen = FloatString.Len();
			if(StringLen > 4)
			{
				FloatString = FloatString.Left(4);
			}
			else if(StringLen<4)
			{
				FloatString = FloatString.Append("0", 4 - StringLen);
			}
		}
		else
		{
			FloatString = FloatString.Left(3);
		}
	}
	else
	{
		float ScaledValue = CurrentValue/1000.0f;
		FloatString = FString::SanitizeFloat(ScaledValue);

		if(ScaledValue < 10.0f)
		{
			FloatString = FloatString.Left(3).Append(TEXT("k"));
		}
		else
		{
			FloatString = FloatString.Left(2).Append(TEXT("k"));
		}
	}
	CurrentValueText = FText::FromString(FloatString);
}

void UStatusBarBase::UpdateWidget()
{
	//Safety Check

	if(!PercentBar_Filled || !PercentBar_Empty || !IconImage)
	{
		return;
	}

	FSlateChildSize EmptySize = FSlateChildSize(ESlateSizeRule::Fill);
	EmptySize.Value = 1.0f - CurrentPercentage;

	FSlateChildSize FilledSize = FSlateChildSize(ESlateSizeRule::Fill);
	FilledSize.Value = CurrentPercentage;

	if(UHorizontalBoxSlot* FilledSlot = Cast<UHorizontalBoxSlot>(PercentBar_Filled->Slot))
	{
		FilledSlot->SetSize(FilledSize);
	}

	if(UHorizontalBoxSlot* EmptySlot = Cast<UHorizontalBoxSlot>(PercentBar_Empty->Slot))
	{
		EmptySlot->SetSize(EmptySize);
	}

	PercentBar_Filled->SetBrushColor(BarForegroundColor);
	IconImage->SetBrush(IconBrush);

	ProcessCurrentValueText();
	ValueText->SetText(CurrentValueText);
	PercentBars->SetVisibility(IsFullSize ? ESlateVisibility::Visible:ESlateVisibility::Collapsed);
}
