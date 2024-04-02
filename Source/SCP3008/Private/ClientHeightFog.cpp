// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientHeightFog.h"

AClientHeightFog::AClientHeightFog()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    
    // set is relevant only to owner to true
    bOnlyRelevantToOwner = true;

  
    bAlwaysRelevant = false;
}

bool AClientHeightFog::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
    return RealViewer == GetOwner();
}