#include "Player/HeatGaugeComponent.h"

UHeatGaugeComponent::UHeatGaugeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeatGaugeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bOverheated)
	{
		OverheatRecoveryElapsed += DeltaTime;
		if (OverheatRecoveryElapsed >= OverheatRecoveryDuration)
		{
			bOverheated = false;
			OverheatRecoveryElapsed = 0.f;
			SetHeat(0.f);
			OnOverheatRecovered.Broadcast();
		}
		return;
	}

	if (CurrentHeat > 0.f)
	{
		SetHeat(FMath::Max(0.f, CurrentHeat - PassiveCooldownRate * DeltaTime));
	}
}

void UHeatGaugeComponent::AddHeatFromShot()
{
	if (bOverheated)
	{
		return;
	}

	SetHeat(CurrentHeat + HeatPerShot);

	if (GetHeat01() >= OverheatThreshold01)
	{
		EnterOverheat();
	}
}

void UHeatGaugeComponent::SetHeat(float NewHeat)
{
	NewHeat = FMath::Clamp(NewHeat, 0.f, MaxHeat);
	if (!FMath::IsNearlyEqual(NewHeat, CurrentHeat))
	{
		CurrentHeat = NewHeat;
		OnHeatChanged.Broadcast(GetHeat01());
	}
}

void UHeatGaugeComponent::EnterOverheat()
{
	bOverheated = true;
	OverheatRecoveryElapsed = 0.f;
	OnOverheat.Broadcast();
}
