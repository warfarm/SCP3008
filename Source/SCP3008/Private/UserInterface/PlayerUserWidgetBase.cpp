// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerUserWidgetBase.h"

#if WITH_EDITOR
const FText UPlayerUserWidgetBase::GetPaletteCategory()
{
	return NSLOCTEXT("UMG", "CustomPaletteCategory", "Development");
}
#endif