// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

using UnrealBuildTool;
using System.Collections.Generic;

public class VRSurvivalGameEditorTarget : TargetRules
{
	public VRSurvivalGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "VRSurvivalGame" } );
	}
}
