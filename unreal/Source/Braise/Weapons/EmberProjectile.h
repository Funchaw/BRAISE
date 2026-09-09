#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmberProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

/**
 * Projectile de tir principal de Tison. Vitesse moderee assumee (voir
 * docs/00-analyse/01-analyse-gameplay.md : la lenteur du projectile
 * favorise l'anticipation plutot que le spam).
 */
UCLASS()
class BRAISE_API AEmberProjectile : public AActor
{
	GENERATED_BODY()

public:
	AEmberProjectile();

	UPROPERTY(BlueprintReadWrite, Category = "Braise|Weapon")
	float Damage = 5.f;

	/** Renforce visuellement/numeriquement quand tire a jauge de chaleur haute (UHeatGaugeComponent::IsEmpowered). */
	UPROPERTY(BlueprintReadWrite, Category = "Braise|Weapon")
	bool bEmpowered = false;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Braise|Weapon")
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Braise|Weapon")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Braise|Weapon")
	float LifeSpanSeconds = 3.f;
};
