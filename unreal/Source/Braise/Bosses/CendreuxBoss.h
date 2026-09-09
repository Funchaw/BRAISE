#pragma once

#include "CoreMinimal.h"
#include "Enemies/CendreuxBase.h"
#include "CendreuxBoss.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossPhaseChanged, int32, NewPhaseIndex);

/**
 * Boss/mini-boss a "corruption visible" plutot que barre de vie classique
 * (fiche mecanique 5, docs/00-analyse/02-fiches-mecaniques.md). Les
 * seuils de vie declenchent un changement de phase ; le Blueprint enfant
 * (BP_Boss_*) reagit a OnBossPhaseChanged pour changer materiaux/VFX/
 * pattern d'attaque -- ce C++ ne fait que detecter les seuils.
 */
UCLASS()
class BRAISE_API ACendreuxBoss : public ACendreuxBase
{
	GENERATED_BODY()

public:
	ACendreuxBoss();

	/** Seuils de vie (0-1, ordre decroissant) declenchant un changement de phase. Ex: [0.5] = 2 phases. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Boss")
	TArray<float> PhaseHealthThresholds;

	UPROPERTY(BlueprintReadOnly, Category = "Braise|Boss")
	int32 CurrentPhaseIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Boss")
	FOnBossPhaseChanged OnPhaseChanged;

	virtual void ApplyDamage(float Amount) override;
};
