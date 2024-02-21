// Fill out your copyright notice in the Description page of Project Settings.


#include "ThePlayer.h"

// Sets default values
AThePlayer::AThePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

