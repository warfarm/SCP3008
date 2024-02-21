// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IkeaEmployee.generated.h"

enum EnemyState { PATROL, CHASE, IDLE, STUNNED};


UCLASS()
class SCP3008_API AIkeaEmployee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIkeaEmployee();
	EnemyState ActorState;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// controls switching between randomized states (patrol, idle)
	// 0 = patrol, 1 = idle ie. [0][1] = chamce of going from patrol to idle
	static TArray<TArray<float>> markovMatrix;
	// Switches state using the markov matrix. If bOverride is true, the state will be forced to change even if it isn't in a randomized state
	// using a reference in current implementation, but could be changed to a return value 
	void SwitchState(EnemyState& currentState, bool bOverride = false);
};
