#include "Progression/UpgradeManagerComponent.h"
#include "Progression/UpgradeDefinition.h"
#include "Player/BraiseCharacter.h"

UUpgradeManagerComponent::UUpgradeManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUpgradeManagerComponent::HandleLevelUp(int32 NewLevel)
{
	const TArray<UUpgradeDefinition*> Choices = RollWeightedChoices();
	if (Choices.Num() > 0)
	{
		OnUpgradeChoicesReady.Broadcast(Choices);
	}
}

void UUpgradeManagerComponent::SelectUpgrade(UUpgradeDefinition* Chosen)
{
	if (!Chosen)
	{
		return;
	}

	int32& Ranks = RanksTaken.FindOrAdd(Chosen);
	Ranks++;

	if (ABraiseCharacter* Character = Cast<ABraiseCharacter>(GetOwner()))
	{
		Chosen->ApplyToCharacter(Character);
	}
}

float UUpgradeManagerComponent::GetWeightForRarity(UUpgradeDefinition* Upgrade) const
{
	// Ponderation Tison/Flamme/Braise -- voir docs/04-progression/xp-et-competences.md.
	switch (Upgrade->Rarity)
	{
	case EUpgradeRarity::Tison:  return 60.f;
	case EUpgradeRarity::Flamme: return 30.f;
	case EUpgradeRarity::Braise: return 10.f;
	default: return 1.f;
	}
}

TArray<UUpgradeDefinition*> UUpgradeManagerComponent::RollWeightedChoices() const
{
	TArray<UUpgradeDefinition*> Pool;
	for (UUpgradeDefinition* Upgrade : AvailableUpgrades)
	{
		if (!Upgrade)
		{
			continue;
		}
		const int32* Taken = RanksTaken.Find(Upgrade);
		const int32 RanksSoFar = Taken ? *Taken : 0;
		if (RanksSoFar < Upgrade->MaxRanks)
		{
			Pool.Add(Upgrade);
		}
	}

	TArray<UUpgradeDefinition*> Result;
	const int32 NumToPick = FMath::Min(ChoicesPerLevelUp, Pool.Num());

	for (int32 i = 0; i < NumToPick; ++i)
	{
		float TotalWeight = 0.f;
		for (UUpgradeDefinition* Candidate : Pool)
		{
			TotalWeight += GetWeightForRarity(Candidate);
		}

		if (TotalWeight <= 0.f)
		{
			break;
		}

		float Roll = FMath::FRandRange(0.f, TotalWeight);
		for (int32 j = 0; j < Pool.Num(); ++j)
		{
			Roll -= GetWeightForRarity(Pool[j]);
			if (Roll <= 0.f)
			{
				Result.Add(Pool[j]);
				Pool.RemoveAt(j);
				break;
			}
		}
	}

	return Result;
}
