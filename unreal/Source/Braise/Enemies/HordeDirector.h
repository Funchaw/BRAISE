#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HordeDirector.generated.h"

class UCendreuxDefinition;
class ACendreuxBase;

USTRUCT(BlueprintType)
struct FCendreuxSpawnEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	TObjectPtr<UCendreuxDefinition> Definition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	TSubclassOf<ACendreuxBase> CendreuxClass;
};

/**
 * Spawn les Cendreux avec une pression croissante dans le temps ET avec
 * la contribution de menace du joueur (jauge de chaleur -- voir GDD v2,
 * section "synergie chaleur x XP", le differenciateur principal du jeu).
 *
 * Version prototype : une seule zone, courbe de spawn simple. Le
 * decoupage par biome (docs/03-bestiaire/bestiaire.md) viendra en
 * vertical slice via un FCendreuxSpawnEntry par biome charge au chargement
 * du niveau.
 */
UCLASS()
class BRAISE_API AHordeDirector : public AActor
{
	GENERATED_BODY()

public:
	AHordeDirector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	TArray<FCendreuxSpawnEntry> SpawnTable;

	/** Cendreux par seconde au debut du run. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	float BaseSpawnRate = 0.5f;

	/** Cendreux par seconde ajoutes par minute ecoulee. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	float SpawnRateGrowthPerMinute = 0.6f;

	/** Poids additionnel de la contribution de chaleur du joueur (0 = ignoree). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	float HeatContributionWeight = 1.5f;

	/** Rayon autour du joueur ou les Cendreux apparaissent (anneau hors-champ). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Braise|Horde")
	float SpawnRingRadius = 1200.f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float ElapsedSeconds = 0.f;
	float SpawnAccumulator = 0.f;

	float GetCurrentSpawnRate() const;
	void SpawnOneCendreux();
	const FCendreuxSpawnEntry* PickWeightedEntry() const;
};
