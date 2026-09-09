#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BraiseCharacter.generated.h"

class UHeatGaugeComponent;
class UXPComponent;
class UWeaponComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * Tison, l'esprit-braise incarne par le joueur (voir docs/01-concepts/braise-gdd-v2.md).
 *
 * Deplacement libre en zone semi-ouverte (pas de defilement force -- voir
 * pivot v2). La logique de mouvement/input reste volontairement simple ici
 * ; le detail des reglages (vitesse, inertie -- fiche mecanique 2) se
 * regle sur les CharacterMovementComponent dans le Blueprint enfant
 * BP_Tison, pas en dur dans ce C++.
 */
UCLASS()
class BRAISE_API ABraiseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABraiseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Braise")
	TObjectPtr<UHeatGaugeComponent> HeatGauge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Braise")
	TObjectPtr<UXPComponent> XPComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Braise")
	TObjectPtr<UWeaponComponent> WeaponComponent;

	/** Assigne dans BP_Tison. Contexte Enhanced Input du joueur. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Input")
	TObjectPtr<UInputAction> MoveAction;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void HandleMove(const FInputActionValue& Value);
};
