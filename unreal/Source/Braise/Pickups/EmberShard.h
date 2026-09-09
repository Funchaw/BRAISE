#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmberShard.generated.h"

class USphereComponent;

/**
 * Eclat de Braise -- XP lache par un Cendreux a sa mort (voir
 * docs/04-progression/xp-et-competences.md). Attire le joueur dans
 * PickupRadius par magnetisme progressif, applique l'XP au contact.
 */
UCLASS()
class BRAISE_API AEmberShard : public AActor
{
	GENERATED_BODY()

public:
	AEmberShard();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|XP")
	int32 XPValue = 1;

	/** Distance a partir de laquelle l'Eclat commence a etre attire vers le joueur. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|XP")
	float MagnetRadius = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|XP")
	float MagnetSpeed = 900.f;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Braise|XP")
	TObjectPtr<USphereComponent> CollisionSphere;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TWeakObjectPtr<APawn> HomingTarget;
};
