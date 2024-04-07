// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/Main/GraphicSettingManager.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

void UGraphicSettingManager::NativeConstruct() {
	GameUserSettings = UGameUserSettings::GetGameUserSettings();

	InitializeResolutionComboBox();
	InitializeVSync();
	InitializeGraphicQuality();
}

UWidget* UGraphicSettingManager::NativeGetDesiredFocusTarget() const {
	return Super::NativeGetDesiredFocusTarget();
}

//initializes
void UGraphicSettingManager::InitializeVSync() {
	VSyncCheckBox->SetIsChecked(GameUserSettings->IsVSyncEnabled());
	VSyncCheckBox->OnCheckStateChanged.Clear();
	VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UGraphicSettingManager::OnVSyncChanged);

}

void UGraphicSettingManager::InitializeGraphicQuality() {
	GraphicSettings.Reset();
	GraphicSettings = { 0,1,2,3 };

	//make the dropdown
	GraphicSettingComboBox->ClearOptions();
	for (const auto& Setting : GraphicSettings) {
		const auto SettingString = FString::Printf(TEXT("%d"), Setting);
		GraphicSettingComboBox->AddOption(SettingString);
	}

	const auto CurrentGraphicSettings = GameUserSettings->GetOverallScalabilityLevel();
	const auto SelectedIndex = GraphicSettings.IndexOfByPredicate([&CurrentGraphicSettings]
	(const int& InGraphicSetting) {
			return InGraphicSetting == CurrentGraphicSettings;
		});

	check(SelectedIndex >= 0)
		GraphicSettingComboBox->SetSelectedIndex(SelectedIndex);

	//when there's changes
	GraphicSettingComboBox->OnSelectionChanged.AddDynamic(this, &UGraphicSettingManager::OnGraphicSettingChanged);
	GraphicSettingComboBox->OnSelectionChanged.Clear();
	
}

void UGraphicSettingManager::InitializeResolutionComboBox() {
	Resolutions.Reset();
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	//makes the dropdown
	ResolutionComboBox->ClearOptions();
	for (const auto& Resolution : Resolutions) {
		const auto ResolutionString = FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}

	//sets the default resolution
	const auto CurrentResolution = GameUserSettings->GetScreenResolution();
	const auto SelectedIndex = Resolutions.IndexOfByPredicate([&CurrentResolution]
	(const FIntPoint& InResolution) {
			return InResolution == CurrentResolution;
		});

		check(SelectedIndex >= 0)
			ResolutionComboBox->SetSelectedIndex(SelectedIndex);

	//changes to box
		ResolutionComboBox->OnSelectionChanged.Clear();
		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UGraphicSettingManager::OnResolutionChanged);
}

//change functions
void UGraphicSettingManager::OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType) {
	const auto SelectedResolution = Resolutions[ResolutionComboBox->GetSelectedIndex()];
	GameUserSettings->SetScreenResolution(SelectedResolution);
	GameUserSettings->ApplySettings(false);
}

void UGraphicSettingManager::OnVSyncChanged(bool InIsChecked) {
	GameUserSettings->SetVSyncEnabled(InIsChecked);
	GameUserSettings->ApplySettings(false);
}

void UGraphicSettingManager::OnGraphicSettingChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType) {
	const auto SelectedGraphicSetting = GraphicSettings[GraphicSettingComboBox->GetSelectedIndex()];
	GameUserSettings->SetOverallScalabilityLevel(SelectedGraphicSetting);
	GameUserSettings->ApplySettings(false);
}
