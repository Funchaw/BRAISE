#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AEmberProjectile;
class UHeatGaugeComponent;

/**
 * Tir automatique vers l'ennemi le plus proche (choix du prototype, voir
 * docs/02-prototype/prototype-ue5.md -- a reevaluer face a un tir dirige
 * apres test). Alimente et lit UHeatGaugeComponent pour le renforcement
 * de tir a jauge haute.
 */
UCLASS(ClassGroup = (Braise), meta = (BlueprintSpawnableComponent))
class BRAISE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Weapon")
	TSubclassOf<AEmberProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Weapon")
	float BaseFireRate = 2.f; // tirs par seconde

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Weapon")
	float BaseDamage = 5.f;

	/** Multiplicateur de degats applique quand la jauge de chaleur est "empowered". */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Weapon")
	float EmpoweredDamageMultiplier = 1.75f;

	/** Rayon de recherche de cible pour le tir automatique. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Weapon")
	float TargetSearchRadius = 800.f;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TimeSinceLastShot = 0.f;
	TWeakObjectPtr<UHeatGaugeComponent> CachedHeatGauge;

	AActor* FindNearestEnemy() const;
	void Fire(AActor* Target);
};
