#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeatGaugeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeatChanged, float, NewHeat01);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverheat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverheatRecovered);

/**
 * Mecanique signature de Braise ("Charge et Braise", voir
 * docs/00-analyse/02-fiches-mecaniques.md, fiche 1).
 *
 * Tirer augmente la chaleur. Une chaleur haute renforce les tirs (voir
 * UWeaponComponent) mais rend le joueur plus visible/dangereux a
 * proximite (le Directeur de Horde peut lire cette valeur pour ajuster
 * la difficulte -- voir AHordeDirector). Au-dela du seuil de surchauffe,
 * le joueur entre dans une fenetre de vulnerabilite temporaire.
 */
UCLASS(ClassGroup = (Braise), meta = (BlueprintSpawnableComponent))
class BRAISE_API UHeatGaugeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHeatGaugeComponent();

	/** Chaleur actuelle, 0 a MaxHeat. */
	UPROPERTY(BlueprintReadOnly, Category = "Braise|Heat")
	float CurrentHeat = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Heat")
	float MaxHeat = 100.f;

	/** Chaleur gagnee par tir (voir UWeaponComponent::Fire). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Heat")
	float HeatPerShot = 8.f;

	/** Vitesse de refroidissement passif (unites/seconde) quand on ne tire pas. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Heat")
	float PassiveCooldownRate = 15.f;

	/** Fraction de MaxHeat au-dela de laquelle le tir est renforce. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Heat", meta = (ClampMin = "0", ClampMax = "1"))
	float EmpoweredThreshold01 = 0.7f;

	/** Fraction de MaxHeat au-dela de laquelle la surchauffe se declenche. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Heat", meta = (ClampMin = "0", ClampMax = "1"))
	float OverheatThreshold01 = 1.f;

	/** Duree de la fenetre de vulnerabilite apres surchauffe (secondes). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Braise|Heat")
	float OverheatRecoveryDuration = 2.5f;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Heat")
	FOnHeatChanged OnHeatChanged;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Heat")
	FOnOverheat OnOverheat;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Heat")
	FOnOverheatRecovered OnOverheatRecovered;

	/** Appele par le systeme de tir a chaque coup. Ignore si en surchauffe. */
	UFUNCTION(BlueprintCallable, Category = "Braise|Heat")
	void AddHeatFromShot();

	UFUNCTION(BlueprintCallable, Category = "Braise|Heat")
	float GetHeat01() const { return MaxHeat > 0.f ? CurrentHeat / MaxHeat : 0.f; }

	UFUNCTION(BlueprintCallable, Category = "Braise|Heat")
	bool IsEmpowered() const { return !bOverheated && GetHeat01() >= EmpoweredThreshold01; }

	UFUNCTION(BlueprintCallable, Category = "Braise|Heat")
	bool IsOverheated() const { return bOverheated; }

	/** Le Directeur de Horde lit cette valeur pour ajuster la pression de spawn. */
	UFUNCTION(BlueprintCallable, Category = "Braise|Heat")
	float GetThreatContribution01() const { return GetHeat01(); }

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bOverheated = false;
	float OverheatRecoveryElapsed = 0.f;

	void SetHeat(float NewHeat);
	void EnterOverheat();
};
