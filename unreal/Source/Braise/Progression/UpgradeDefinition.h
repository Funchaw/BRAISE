#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeDefinition.generated.h"

class ABraiseCharacter;

/** Categories de competences -- voir docs/04-progression/xp-et-competences.md. */
UENUM(BlueprintType)
enum class EUpgradeCategory : uint8
{
	Feu			UMETA(DisplayName = "Feu"),
	Chaleur		UMETA(DisplayName = "Chaleur"),
	Mobilite	UMETA(DisplayName = "Mobilite"),
	Defense		UMETA(DisplayName = "Defense"),
	Utilitaire	UMETA(DisplayName = "Utilitaire")
};

/** Rarete de tirage -- ponderation du pool (voir document XP & competences). */
UENUM(BlueprintType)
enum class EUpgradeRarity : uint8
{
	Tison		UMETA(DisplayName = "Tison (Commune)"),
	Flamme		UMETA(DisplayName = "Flamme (Rare)"),
	Braise		UMETA(DisplayName = "Braise (Legendaire)")
};

/**
 * Une competence proposable en montee de niveau. Une instance = un
 * asset de donnees cree dans le Content Browser (clic droit > Miscellaneous
 * > Data Asset > UpgradeDefinition), pas de code par competence : le
 * designer ajoute des competences sans toucher au C++.
 *
 * L'application effective de l'effet reste volontairement generique
 * (ApplyToCharacter) : au prototype, on peut l'implementer en Blueprint
 * enfant de UUpgradeDefinition pour chaque competence (BP_Upgrade_*),
 * ou passer par un systeme de tags/modificateurs plus tard si le nombre
 * de competences grossit trop pour rester lisible en Blueprint.
 */
UCLASS(BlueprintType)
class BRAISE_API UUpgradeDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Upgrade")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Upgrade", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Upgrade")
	EUpgradeCategory Category = EUpgradeCategory::Feu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Upgrade")
	EUpgradeRarity Rarity = EUpgradeRarity::Tison;

	/** Nombre maximum de fois que cette competence peut etre choisie dans un run. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Upgrade")
	int32 MaxRanks = 1;

	/** A implementer en Blueprint enfant : applique l'effet au personnage. */
	UFUNCTION(BlueprintNativeEvent, Category = "Braise|Upgrade")
	void ApplyToCharacter(ABraiseCharacter* Character);
	virtual void ApplyToCharacter_Implementation(ABraiseCharacter* Character) {}
};
