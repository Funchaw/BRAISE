#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeManagerComponent.generated.h"

class UUpgradeDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeChoicesReady, const TArray<UUpgradeDefinition*>&, Choices);

/**
 * Ecoute UXPComponent::OnLevelUp et propose 3 competences aleatoires
 * ponderees par rarete (voir docs/04-progression/xp-et-competences.md).
 * La presentation (UI de choix) reste au niveau UMG/Blueprint : ce
 * composant ne fait que la logique de tirage + l'application du choix.
 */
UCLASS(ClassGroup = (Braise), meta = (BlueprintSpawnableComponent))
class BRAISE_API UUpgradeManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUpgradeManagerComponent();

	/** Pool de competences disponibles. Rempli dans BP_Tison ou via une Data Table au vertical slice. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Upgrade")
	TArray<TObjectPtr<UUpgradeDefinition>> AvailableUpgrades;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Upgrade")
	int32 ChoicesPerLevelUp = 3;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Upgrade")
	FOnUpgradeChoicesReady OnUpgradeChoicesReady;

	/** A binder sur UXPComponent::OnLevelUp (BeginPlay du personnage). */
	UFUNCTION(BlueprintCallable, Category = "Braise|Upgrade")
	void HandleLevelUp(int32 NewLevel);

	/** Appele par l'UI de choix de competence quand le joueur valide. */
	UFUNCTION(BlueprintCallable, Category = "Braise|Upgrade")
	void SelectUpgrade(UUpgradeDefinition* Chosen);

private:
	UPROPERTY()
	TMap<TObjectPtr<UUpgradeDefinition>, int32> RanksTaken;

	TArray<UUpgradeDefinition*> RollWeightedChoices() const;
	float GetWeightForRarity(UUpgradeDefinition* Upgrade) const;
};
