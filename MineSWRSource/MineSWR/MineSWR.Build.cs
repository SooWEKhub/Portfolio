// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MineSWR : ModuleRules
{
	public MineSWR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "WebSockets" });
	}
}
