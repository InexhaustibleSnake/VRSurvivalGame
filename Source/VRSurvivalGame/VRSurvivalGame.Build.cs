// The project was made by Alexey Guchmazov Ilich (Inexhaustible Snake) for educational purposes

using UnrealBuildTool;

public class VRSurvivalGame : ModuleRules
{
	public VRSurvivalGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PublicIncludePaths.AddRange(new string[] { "EnhancedInput/Public" });

        PrivateDependencyModuleNames.AddRange(new string[] { "HeadMountedDisplay" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
