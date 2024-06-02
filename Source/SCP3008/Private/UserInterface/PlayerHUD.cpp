// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerHUD.h"
#include "Players/MainCharacter.h"
#include "UserInterface/StatusBarBase.h"
#include "UserInterface/BasicLayoutBase.h"
#include "UserInterface/MinimalLayoutBase.h"
#include "UserInterface/MaximumLayoutBase.h"
#include "UserInterface/StatusHUDBase.h"

void APlayerHUD::SetCurrentViewMode(EHUDViewMode NewViewMode)
{
	CurrentViewMode = NewViewMode;
	UpdateWidgets();
}

void APlayerHUD::CycleToNextViewMode()
{
	++CurrentViewMode;
	//UE_LOG(BBLog, Warning, TEXT("CycleToNextViewMode %s"), *UEnum::GetValueAsString(CurrentViewMode));
	UpdateWidgets();
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	//Get World Reference
	World = GetWorld();
	checkf(World, TEXT("Get World Failed"))

	//Ensure All UI Presets exist
	checkf(MinimalLayoutClass, TEXT("Get MinimalLayoutClass Failed"))
	checkf(BasicLayoutClass, TEXT("Get BasicLayoutClass Failed"))
	checkf(MaximumLayoutClass, TEXT("Get MaximumLayoutClass Failed"))

	MinimalLayoutWidget = CreateWidget<UMinimalLayoutBase>(World, MinimalLayoutClass);
	MinimalLayoutWidget->AddToViewport();
	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	BasicLayoutWidget = CreateWidget<UBasicLayoutBase>(World, BasicLayoutClass);
	BasicLayoutWidget->AddToViewport();
	BasicLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	MaximumLayoutWidget = CreateWidget<UMaximumLayoutBase>(World, MaximumLayoutClass);
	MaximumLayoutWidget->AddToViewport();
	MaximumLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	if(APlayerController* PlayerController = GetOwningPlayerController())
	{
		PlayerCharacter = Cast<AMainCharacter>(PlayerController->GetPawn());
	}

	checkf(PlayerCharacter, TEXT("Unable to get a reference to the player character"));

	UpdateWidgets();
}

void APlayerHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearAllHandlers();
	
	Super::EndPlay(EndPlayReason);
}

void APlayerHUD::UpdateWidgets()
{
	ClearAllHandlers();

	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	BasicLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	MaximumLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	switch (CurrentViewMode)
	{
	case EHUDViewMode::Clean:
		break;
	case EHUDViewMode::Minimal:
		PlayerCharacter->OnHealthChanged.AddDynamic(MinimalLayoutWidget->StatusHUDBase->HealthBar, &UStatusBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(MinimalLayoutWidget->StatusHUDBase->StaminaBar, &UStatusBarBase::OnFloatStatUpdated);
		PlayerCharacter->OnHungerChanged.AddDynamic(MinimalLayoutWidget->StatusHUDBase->HungerBar, &UStatusBarBase::OnIntStatUpdated);
		PlayerCharacter->OnThirstChanged.AddDynamic(MinimalLayoutWidget->StatusHUDBase->ThirstBar, &UStatusBarBase::OnIntStatUpdated);
		MinimalLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EHUDViewMode::Basic:
		PlayerCharacter->OnHealthChanged.AddDynamic(BasicLayoutWidget->StatusHUDBase->HealthBar, &UStatusBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(BasicLayoutWidget->StatusHUDBase->StaminaBar, &UStatusBarBase::OnFloatStatUpdated);
		PlayerCharacter->OnHungerChanged.AddDynamic(BasicLayoutWidget->StatusHUDBase->HungerBar, &UStatusBarBase::OnIntStatUpdated);
		PlayerCharacter->OnThirstChanged.AddDynamic(BasicLayoutWidget->StatusHUDBase->ThirstBar, &UStatusBarBase::OnIntStatUpdated);
		BasicLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EHUDViewMode::Maximum:
		PlayerCharacter->OnHealthChanged.AddDynamic(MaximumLayoutWidget->StatusHUDBase->HealthBar, &UStatusBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(MaximumLayoutWidget->StatusHUDBase->StaminaBar, &UStatusBarBase::OnFloatStatUpdated);
		PlayerCharacter->OnHungerChanged.AddDynamic(MaximumLayoutWidget->StatusHUDBase->HungerBar, &UStatusBarBase::OnIntStatUpdated);
		PlayerCharacter->OnThirstChanged.AddDynamic(MaximumLayoutWidget->StatusHUDBase->ThirstBar, &UStatusBarBase::OnIntStatUpdated);
		MaximumLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	default:;
	}

	PlayerCharacter->BroadcastCurrentStats();
	
}

void APlayerHUD::ClearAllHandlers()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->OnHealthChanged.Clear();
		PlayerCharacter->OnStaminaChanged.Clear();
		PlayerCharacter->OnHungerChanged.Clear();
		PlayerCharacter->OnThirstChanged.Clear();
	}
}
