// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MPRPG : ModuleRules
{
	public MPRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
