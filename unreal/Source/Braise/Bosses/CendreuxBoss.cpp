#include "Bosses/CendreuxBoss.h"

ACendreuxBoss::ACendreuxBoss()
{
	// Exemple par defaut pour le prototype : 2 phases (voir
	// docs/02-prototype/prototype-ue5.md). A ajuster par boss en Blueprint.
	PhaseHealthThresholds.Add(0.5f);
}

void ACendreuxBoss::ApplyDamage(float Amount)
{
	Super::ApplyDamage(Amount);

	if (CurrentPhaseIndex < PhaseHealthThresholds.Num())
	{
		const float Threshold = PhaseHealthThresholds[CurrentPhaseIndex];
		if (GetHealth01() <= Threshold)
		{
			CurrentPhaseIndex++;
			OnPhaseChanged.Broadcast(CurrentPhaseIndex);
		}
	}
}
