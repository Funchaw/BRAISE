using UnrealBuildTool;

public class Braise : ModuleRules
{
	public Braise(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Module a plat (pas de sous-dossiers Public/Private) : sans cette
		// ligne, UBT n'ajoute pas la racine du module au chemin d'inclusion,
		// et des includes comme "Player/BraiseCharacter.h" (ecrits relatifs
		// a Source/Braise/) ne se resolvent pas -- erreur C1083.
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"NavigationSystem",
			"Niagara",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});
	}
}
