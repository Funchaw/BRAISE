#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CendreuxBase.generated.h"

class UCendreuxDefinition;
class ACendreuxBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCendreuxHealthChanged, float, Health01);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCendreuxDeath, ACendreuxBase*, Dead);

/**
 * Base commune a tous les Cendreux (voir docs/03-bestiaire/bestiaire.md).
 * Le comportement precis par archetype (fonce / tire / charge / explose /
 * zone d'effet) est implemente en Blueprint enfant via l'Event
 * "OnArchetypeTick", pour que le C++ reste generique et que le contenu
 * (nouveaux Cendreux) se cree sans recompiler.
 *
 * La sequence Telegraph -> Attack est cependant geree ici en C++ car
 * c'est une regle transversale non negociable du jeu (fiche mecanique 3 :
 * toute attaque dangereuse doit etre telegraphee).
 */
UCLASS()
class BRAISE_API ACendreuxBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACendreuxBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Braise|Cendreux")
	TObjectPtr<UCendreuxDefinition> Definition;

	UPROPERTY(BlueprintReadOnly, Category = "Braise|Cendreux")
	float CurrentHealth = 0.f;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Cendreux")
	FOnCendreuxHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Cendreux")
	FOnCendreuxDeath OnDeath;

	UFUNCTION(BlueprintCallable, Category = "Braise|Cendreux")
	virtual void ApplyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Braise|Cendreux")
	float GetHealth01() const { return Definition && Definition->MaxHealth > 0.f ? CurrentHealth / Definition->MaxHealth : 0.f; }

	/** Lance la sequence tell -> attaque. A appeler depuis le Blueprint enfant quand la cible est a portee. */
	UFUNCTION(BlueprintCallable, Category = "Braise|Cendreux")
	void BeginTelegraphedAttack();

	/** Implemente en Blueprint : joue le VFX/anim de tell. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Braise|Cendreux")
	void OnTelegraphStart();

	/** Implemente en Blueprint : execute l'attaque effective (spawn projectile, zone, charge...). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Braise|Cendreux")
	void OnAttackExecute();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TelegraphTimerHandle;
	void ExecuteAttackAfterTelegraph();

	virtual void Die();
};
