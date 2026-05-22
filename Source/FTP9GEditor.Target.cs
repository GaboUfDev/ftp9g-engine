using UnrealBuildTool;
using System.Collections.Generic;

public class FTP9GEditorTarget : TargetRules
{
	public FTP9GEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("FTP9G");
	}
}
