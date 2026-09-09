#include "Progression/XPComponent.h"

UXPComponent::UXPComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UXPComponent::AddXP(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	CurrentXP += Amount;
	OnXPChanged.Broadcast(CurrentXP, GetXPRequiredForNextLevel());
	TryLevelUp();
}

int32 UXPComponent::GetXPRequiredForNextLevel() const
{
	// Niveau 1->2 coute BaseXPToLevel, chaque niveau suivant coute
	// BaseXPToLevel * XPCurveMultiplier^(niveau-1). Courbe volontairement
	// simple pour le prototype -- a retravailler en vertical slice avec
	// une Curve Table pour un controle fin par designer.
	return FMath::RoundToInt(BaseXPToLevel * FMath::Pow(XPCurveMultiplier, CurrentLevel - 1));
}

void UXPComponent::TryLevelUp()
{
	int32 Required = GetXPRequiredForNextLevel();
	while (CurrentXP >= Required)
	{
		CurrentXP -= Required;
		CurrentLevel++;
		OnLevelUp.Broadcast(CurrentLevel);
		Required = GetXPRequiredForNextLevel();
	}
}
