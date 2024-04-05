// Fill out your copyright notice in the Description page of Project Settings.


#include "World/InterfaceTestActor.h"
#include "Entities/MainPlayer.h"

// Sets default values
AInterfaceTestActor::AInterfaceTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void AInterfaceTestActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableData = InstanceInteractableData;
}

// Called every frame
void AInterfaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInterfaceTestActor::BeginFocus()
{
	if (Mesh)
	{
		//Mesh->SetRenderCustomDepth(true);
		UE_LOG(LogTemp, Warning, TEXT("Calling BeginFocus"))
	}
}

void AInterfaceTestActor::EndFocus()
{
	if (Mesh)
	{
		//Mesh->SetRenderCustomDepth(false);
		UE_LOG(LogTemp, Warning, TEXT("Calling EndFocus"))
	}
}

void AInterfaceTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract"));
}

void AInterfaceTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract"));
}

void AInterfaceTestActor::Interact(AMainPlayer* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact"));
}

