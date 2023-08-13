// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

using UnrealBuildTool;
using System.Collections.Generic;

public class VRSurvivalGameTarget : TargetRules
{
	public VRSurvivalGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "VRSurvivalGame" } );
	}
}
