// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceChatGameInstance.h"

// Vivox Credentials
#define VIVOX_VOICE_DOMAIN TEXT("mtu1xp.vivox.com")
#define VIVOX_VOICE_ISSUER TEXT("25143-scp30-38904-udash")

#define VIVOX_VOICE_SERVER TEXT("https://unity.vivox.com/appconfig/25143-scp30-38904-udash")
// should be on a secure server
#define VIVOX_VOICE_KEY TEXT("zhaSlpm7kdbacfsQxwWe2gtcimWVM8Zd")


// ^ Secrets

void UVoiceChatGameInstance::Init()
{
	Super::Init();
	InitVivox();
}

void UVoiceChatGameInstance::Shutdown()
{
	Super::Shutdown();
	VivoxVoiceClient->Uninitialize();
}

void UVoiceChatGameInstance::InitVivox()
{
	VivoxVoiceClient = &static_cast<FVivoxCoreModule*>(&FModuleManager::Get().LoadModuleChecked(TEXT("VivoxCore")))->VoiceClient();
	VivoxVoiceClient->Initialize();
	Login();
}

void UVoiceChatGameInstance::Login()
{
	LoggedInUserId = AccountId(VIVOX_VOICE_ISSUER, FGuid::NewGuid().ToString(), VIVOX_VOICE_DOMAIN);
	ILoginSession& LoginSession(VivoxVoiceClient->GetLoginSession(LoggedInUserId));

	FTimespan TokenExpiration = FTimespan::FromSeconds(90);
	FString LoginToken = LoginSession.GetLoginToken(VIVOX_VOICE_KEY,TokenExpiration);

	ILoginSession::FOnBeginLoginCompletedDelegate OnBeginLoginCompleted;
	OnBeginLoginCompleted.BindLambda([this, &LoginSession](VivoxCoreError Error)
	{
		
		UE_LOG(LogTemp, Log, TEXT("Logged into Vivox!"));
		JoinChannel();
	});

	LoginSession.BeginLogin(VIVOX_VOICE_SERVER, LoginToken, OnBeginLoginCompleted);

}

void UVoiceChatGameInstance::JoinChannel()
{
	ILoginSession& LoginSession(VivoxVoiceClient->GetLoginSession(LoggedInUserId));
	ChannelId Channel = ChannelId(VIVOX_VOICE_ISSUER, "MainServer0", VIVOX_VOICE_DOMAIN, ChannelType::Positional);
	IChannelSession& ChannelSession = LoginSession.GetChannelSession(Channel);

	FTimespan TokenExpiration = FTimespan::FromSeconds(90);
	FString ChannelToken = ChannelSession.GetConnectToken(VIVOX_VOICE_KEY, TokenExpiration);

	ChannelSession.BeginConnect(true, false, true, ChannelToken, NULL);
}
