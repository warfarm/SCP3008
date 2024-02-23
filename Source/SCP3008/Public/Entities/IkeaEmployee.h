// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Public/Entities/DefaultMob.h"
#include "IkeaEmployee.generated.h"

/**
 * 
 */
UCLASS()
class AIkeaEmployee : public ADefaultMob
{
	GENERATED_BODY()
public:
	AIkeaEmployee();
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
};
