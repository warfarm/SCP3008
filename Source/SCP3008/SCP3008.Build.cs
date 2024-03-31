// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SCP3008 : ModuleRules
{
	public SCP3008(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SlateCore", "Slate", "UMG", "EnhancedInput", "AIModule", "NavigationSystem", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] { "VivoxCore"});
		
		SetupIrisSupport(Target);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
