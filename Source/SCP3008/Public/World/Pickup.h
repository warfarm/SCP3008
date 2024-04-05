// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/MainPlayer.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Pickup.generated.h"

class UItemBase;

UCLASS()
class SCP3008_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	

   
	// Sets default values for this actor's properties
	APickup();

	void InitializePickup(const TSubclassOf<UItemBase> BaseClass);

	void InitializeDrop(UItemBase* ItemToDrop);

	FORCEINLINE UItemBase* GetItemData() {return ItemReference;}

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;
	
	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Database")
	UDataTable* ItemDataTable;
	
	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Database")
	FName DesiredItemID;
	
	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
	UItemBase* ItemReference;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Pickup | Components")
	FInteractableData InstanceInteractableData;
	
	virtual void BeginPlay() override;

	virtual void Interact(AMainPlayer* Player) override;

	void UpdateInteractableData();
	void TakePickup(const AMainPlayer* Taker);

	UFUNCTION(NetMulticast, Reliable)
	void ServerDestroy();

	void ServerDestroy_Implementation();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
