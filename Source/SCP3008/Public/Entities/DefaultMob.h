// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntitiesInterface.h"
#include "GameFramework/Actor.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "DefaultMob.generated.h"

UENUM()
enum EnemyState { PATROL UMETA(DisplayName = "Patrol"),
	CHASE UMETA(DisplayName = "Chase"),
	IDLE UMETA(DisplayName = "Idle"),
	STUNNED UMETA(DisplayName = "STUNNED")};


UCLASS()
class SCP3008_API ADefaultMob : public AAIController, public IEntitiesInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultMob();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TEnumAsByte<EnemyState> ActorState;
	float IdleTime{5.0f};
	// virtual void Stun(float duration);	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Exits state via SwitchState fucntion
	UFUNCTION(BlueprintCallable, Category = "AI")
	bool ExitAlways();
	// Idles the actor for a set duration
	// virtual void Idle();
	// Exits state via SwitchState function safely
	UFUNCTION(BlueprintCallable, Category = "AI")
	bool ExitSafe();
	
	// 	Makes the actor move to a random location, then idle for a set duration
	UFUNCTION(BlueprintCallable, Category = "AI")
	bool Patrol();
	// 
	

	
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// controls switching between randomized states (patrol, idle)
	// 0 = patrol, 1 = idle ie. [0][1] = chamce of going from patrol to idle
	static  TArray<TArray<float>> markovMatrix;
	// Override this function to set the markov matrix
	virtual void setMarkovChain();
	void HandleState();
private:
	// Switches state using the markov matrix. If bOverride is true, the state will be forced to change even if it isn't in a randomized state
	// using a reference in current implementation, but could be changed to a return value 
	void SwitchState(bool bOverride = false);
	
	

};
