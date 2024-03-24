// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VivoxCore.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VoiceChatGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class SCP3008_API UVoiceChatGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
	virtual void Shutdown() override;

	void InitVivox();
	void Login();
	UFUNCTION(BlueprintCallable, Category="Voice")
	void JoinChannel();

	IClient* VivoxVoiceClient;
	AccountId LoggedInUserId;
	
};
