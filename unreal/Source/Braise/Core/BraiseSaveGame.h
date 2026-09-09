#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BraiseSaveGame.generated.h"

/**
 * Squelette de sauvegarde pour la progression meta (Braisier, Codex --
 * voir docs/01-concepts/braise-gdd-v2.md, section "Progression meta").
 * Explicitement hors perimetre du prototype (docs/02-prototype/) : cette
 * classe existe pour que l'architecture soit prete, pas pour etre
 * cablee/testee des le prototype.
 */
UCLASS()
class BRAISE_API UBraiseSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Braise|Save")
	int32 BraisierCurrency = 0;

	/** Noms (PrimaryAssetId sous forme de FString) des Cendreux deja rencontres -- alimente le Codex. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Braise|Save")
	TArray<FString> DiscoveredCendreux;

	/** Noms des competences debloquees en meta-progression, qui rejoignent le pool de base. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Braise|Save")
	TArray<FString> UnlockedUpgrades;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Braise|Save")
	FString SaveSlotName = TEXT("BraiseSave");
};
