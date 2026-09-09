using UnrealBuildTool;
using System.Collections.Generic;

public class BraiseTarget : TargetRules
{
	public BraiseTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.Add("Braise");
	}
}
