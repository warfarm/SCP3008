// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Public/Entities/DefaultMobController.h"
#include "IkeaEmployeeController.generated.h"

/**
 * 
 */
UCLASS()
class AIkeaEmployeeController : public ADefaultMobController
{
	GENERATED_BODY()
public:
	AIkeaEmployeeController();
protected:
	UPROPERTY(EditAnywhere,Category="Audio")
	float voiceLineFrequency;
	UPROPERTY(EditAnywhere,Category="Audio")
	USoundBase* voiceLines[3];
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	void PlayRandomVoiceLine();

private:
	FTimerHandle voiceLineTimerHandle;
};
