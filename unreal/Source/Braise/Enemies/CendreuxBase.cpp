#include "Enemies/CendreuxBase.h"
#include "Enemies/CendreuxDefinition.h"
#include "Pickups/EmberShard.h"
#include "GameFramework/CharacterMovementComponent.h"

ACendreuxBase::ACendreuxBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACendreuxBase::BeginPlay()
{
	Super::BeginPlay();

	if (Definition)
	{
		CurrentHealth = Definition->MaxHealth;
		GetCharacterMovement()->MaxWalkSpeed = Definition->MoveSpeed;
	}
}

void ACendreuxBase::ApplyDamage(float Amount)
{
	if (Amount <= 0.f || CurrentHealth <= 0.f)
	{
		return;
	}

	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);
	OnHealthChanged.Broadcast(GetHealth01());

	if (CurrentHealth <= 0.f)
	{
		Die();
	}
}

void ACendreuxBase::BeginTelegraphedAttack()
{
	if (!Definition)
	{
		return;
	}

	OnTelegraphStart();

	if (Definition->TelegraphDuration > 0.f)
	{
		GetWorldTimerManager().SetTimer(TelegraphTimerHandle, this, &ACendreuxBase::ExecuteAttackAfterTelegraph, Definition->TelegraphDuration, false);
	}
	else
	{
		ExecuteAttackAfterTelegraph();
	}
}

void ACendreuxBase::ExecuteAttackAfterTelegraph()
{
	OnAttackExecute();
}

void ACendreuxBase::Die()
{
	if (Definition)
	{
		for (int32 i = 0; i < Definition->XPReward; ++i)
		{
			// Spawn simple ; positionnement/eparpillement fin a affiner en Blueprint (BP_CendreuxBase).
			GetWorld()->SpawnActor<AEmberShard>(AEmberShard::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
		}
	}

	OnDeath.Broadcast(this);
	Destroy();
}
