// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalHeightFog.h"
#include "ClientHeightFog.generated.h"

/**
 * 
 */
UCLASS()
class SCP3008_API AClientHeightFog : public ALocalHeightFog
{
	GENERATED_BODY()
	AClientHeightFog();

	// override the net relevancy function ig
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
};
