// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerHUD.h"

#include "Spatial/BlockedDenseGrid3.h"

void APlayerHUD::SetCurrentViewMode(EHUDViewMode NewViewMode)
{
}

void APlayerHUD::CycleToNextViewMode()
{
	//++CurrentViewMode;
	//UE_LOG(BBLog, Warning, TEXT("CycleToNextViewMode %s"), *UEnum::GetValueAsString(CurrentViewMode));
	//UpdateWidgets();
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APlayerHUD::UpdateWidgets()
{
}

void APlayerHUD::ClearAllHandlers()
{
}
