using UnrealBuildTool;
using System.Collections.Generic;

public class BraiseEditorTarget : TargetRules
{
	public BraiseEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.Add("Braise");
	}
}
