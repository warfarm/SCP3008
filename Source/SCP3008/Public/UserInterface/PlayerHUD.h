// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

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

UCLASS()
class SCP3008_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

	
};
