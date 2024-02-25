// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/DefaultMobPawn.h"

// Sets default values
ADefaultMobPawn::ADefaultMobPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultMobPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultMobPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultMobPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}