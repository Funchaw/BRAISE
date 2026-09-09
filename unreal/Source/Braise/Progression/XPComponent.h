#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChanged, int32, CurrentXP, int32, XPToNextLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);

/**
 * Suivi de l'XP et des niveaux (voir docs/04-progression/xp-et-competences.md).
 * Chaque montee de niveau notifie UUpgradeManagerComponent, qui presente
 * les 3 choix de competences -- separation des responsabilites : ce
 * composant ne connait rien du pool de competences.
 */
UCLASS(ClassGroup = (Braise), meta = (BlueprintSpawnableComponent))
class BRAISE_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UXPComponent();

	UPROPERTY(BlueprintReadOnly, Category = "Braise|XP")
	int32 CurrentLevel = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Braise|XP")
	int32 CurrentXP = 0;

	/** XP requise pour le niveau 2. Chaque niveau suivant multiplie ce cout par XPCurveMultiplier. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|XP")
	int32 BaseXPToLevel = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|XP")
	float XPCurveMultiplier = 1.35f;

	UPROPERTY(BlueprintAssignable, Category = "Braise|XP")
	FOnXPChanged OnXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Braise|XP")
	FOnLevelUp OnLevelUp;

	/** Appele par UEmberShard::OnPickedUp (voir Pickups/EmberShard.h). */
	UFUNCTION(BlueprintCallable, Category = "Braise|XP")
	void AddXP(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Braise|XP")
	int32 GetXPRequiredForNextLevel() const;

private:
	void TryLevelUp();
};
