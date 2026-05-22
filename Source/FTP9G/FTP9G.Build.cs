// Copyright FTP9G Project. All Rights Reserved.

using UnrealBuildTool;

public class FTP9G : ModuleRules
{
	public FTP9G(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp20;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Json",
			"JsonUtilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"UMG"
		});

		PublicIncludePaths.AddRange(new string[]
		{
			"FTP9G",
			"FTP9G/Aircraft",
			"FTP9G/FlightModel",
			"FTP9G/Propulsion",
			"FTP9G/FlightControl"
		});
	}
}
