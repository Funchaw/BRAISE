#include "Weapons/WeaponComponent.h"
#include "Weapons/EmberProjectile.h"
#include "Player/HeatGaugeComponent.h"
#include "Enemies/CendreuxBase.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedHeatGauge = GetOwner()->FindComponentByClass<UHeatGaugeComponent>();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CachedHeatGauge.IsValid() && CachedHeatGauge->IsOverheated())
	{
		// En surchauffe : pas de tir, fenetre de vulnerabilite (fiche mecanique 1).
		return;
	}

	TimeSinceLastShot += DeltaTime;
	const float FireInterval = BaseFireRate > 0.f ? 1.f / BaseFireRate : 1.f;

	if (TimeSinceLastShot >= FireInterval)
	{
		if (AActor* Target = FindNearestEnemy())
		{
			Fire(Target);
			TimeSinceLastShot = 0.f;
		}
	}
}

AActor* UWeaponComponent::FindNearestEnemy() const
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACendreuxBase::StaticClass(), Enemies);

	AActor* Nearest = nullptr;
	float NearestDistSq = TargetSearchRadius * TargetSearchRadius;
	const FVector OwnerLocation = GetOwner()->GetActorLocation();

	for (AActor* Enemy : Enemies)
	{
		const float DistSq = FVector::DistSquared(OwnerLocation, Enemy->GetActorLocation());
		if (DistSq <= NearestDistSq)
		{
			NearestDistSq = DistSq;
			Nearest = Enemy;
		}
	}

	return Nearest;
}

void UWeaponComponent::Fire(AActor* Target)
{
	if (!ProjectileClass || !Target)
	{
		return;
	}

	const FVector StartLocation = GetOwner()->GetActorLocation();
	const FRotator AimRotation = (Target->GetActorLocation() - StartLocation).Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEmberProjectile* Projectile = GetWorld()->SpawnActor<AEmberProjectile>(ProjectileClass, StartLocation, AimRotation, SpawnParams);
	if (Projectile)
	{
		const bool bEmpowered = CachedHeatGauge.IsValid() && CachedHeatGauge->IsEmpowered();
		Projectile->Damage = bEmpowered ? BaseDamage * EmpoweredDamageMultiplier : BaseDamage;
		Projectile->bEmpowered = bEmpowered;
	}

	if (CachedHeatGauge.IsValid())
	{
		CachedHeatGauge->AddHeatFromShot();
	}
}
