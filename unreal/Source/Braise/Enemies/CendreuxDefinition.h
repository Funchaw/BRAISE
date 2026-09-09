#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CendreuxDefinition.generated.h"

/** Archetypes de comportement -- voir docs/03-bestiaire/bestiaire.md. */
UENUM(BlueprintType)
enum class ECendreuxArchetype : uint8
{
	BraiseEteint	UMETA(DisplayName = "Braise-eteint (fonce)"),
	CendreVive		UMETA(DisplayName = "Cendre-vive (tir a distance)"),
	Fondu			UMETA(DisplayName = "Fondu (charge)"),
	Eclateur		UMETA(DisplayName = "Eclateur (explose)"),
	Etouffeur		UMETA(DisplayName = "Etouffeur (zone d'effet)")
};

/**
 * Donnees d'un type de Cendreux. Chaque nouvel ennemi = un asset de
 * donnees + un Blueprint enfant de ACendreuxBase pour la mesh/anim/VFX,
 * pas une nouvelle classe C++ (voir regle de conception en fin de
 * docs/03-bestiaire/bestiaire.md).
 */
UCLASS(BlueprintType)
class BRAISE_API UCendreuxDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	ECendreuxArchetype Archetype = ECendreuxArchetype::BraiseEteint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	float MaxHealth = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	float MoveSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	float AttackDamage = 10.f;

	/** Duree du tell avant une attaque (fiche mecanique 3 -- toujours > 0 sauf pression de nombre). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	float TelegraphDuration = 0.4f;

	/** Nombre d'Eclats de Braise (XP) laches a la mort. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	int32 XPReward = 1;

	/** Poids relatif dans le tirage du Directeur de Horde pour ce biome. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	float SpawnWeight = 1.f;
};
