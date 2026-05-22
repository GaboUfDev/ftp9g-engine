using UnrealBuildTool;
using System.Collections.Generic;

public class FTP9GTarget : TargetRules
{
	public FTP9GTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("FTP9G");
	}
}
