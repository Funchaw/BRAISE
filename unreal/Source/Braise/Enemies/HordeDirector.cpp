#include "Enemies/HordeDirector.h"
#include "Enemies/CendreuxBase.h"
#include "Enemies/CendreuxDefinition.h"
#include "Player/BraiseCharacter.h"
#include "Player/HeatGaugeComponent.h"
#include "Kismet/GameplayStatics.h"

AHordeDirector::AHordeDirector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHordeDirector::BeginPlay()
{
	Super::BeginPlay();
}

void AHordeDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedSeconds += DeltaTime;
	SpawnAccumulator += GetCurrentSpawnRate() * DeltaTime;

	while (SpawnAccumulator >= 1.f)
	{
		SpawnOneCendreux();
		SpawnAccumulator -= 1.f;
	}
}

float AHordeDirector::GetCurrentSpawnRate() const
{
	float Rate = BaseSpawnRate + (ElapsedSeconds / 60.f) * SpawnRateGrowthPerMinute;

	// Coeur du differenciateur : plus le joueur brille (chaleur haute),
	// plus la horde s'intensifie -- voir GDD v2, "synergie chaleur x XP".
	if (ABraiseCharacter* Player = Cast<ABraiseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		if (Player->HeatGauge)
		{
			Rate += Player->HeatGauge->GetThreatContribution01() * HeatContributionWeight;
		}
	}

	return Rate;
}

const FCendreuxSpawnEntry* AHordeDirector::PickWeightedEntry() const
{
	if (SpawnTable.Num() == 0)
	{
		return nullptr;
	}

	float TotalWeight = 0.f;
	for (const FCendreuxSpawnEntry& Entry : SpawnTable)
	{
		if (Entry.Definition)
		{
			TotalWeight += Entry.Definition->SpawnWeight;
		}
	}

	if (TotalWeight <= 0.f)
	{
		return &SpawnTable[0];
	}

	float Roll = FMath::FRandRange(0.f, TotalWeight);
	for (const FCendreuxSpawnEntry& Entry : SpawnTable)
	{
		if (!Entry.Definition)
		{
			continue;
		}
		Roll -= Entry.Definition->SpawnWeight;
		if (Roll <= 0.f)
		{
			return &Entry;
		}
	}

	return &SpawnTable.Last();
}

void AHordeDirector::SpawnOneCendreux()
{
	const FCendreuxSpawnEntry* Entry = PickWeightedEntry();
	if (!Entry || !Entry->CendreuxClass)
	{
		return;
	}

	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Player)
	{
		return;
	}

	// Anneau hors-champ autour du joueur -- echo de "apparitions cachees"
	// (fiche mecanique 3), adapte a une zone semi-ouverte sans defilement.
	const float Angle = FMath::FRandRange(0.f, 2.f * PI);
	const FVector Offset = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * SpawnRingRadius;
	const FVector SpawnLocation = Player->GetActorLocation() + Offset;

	// Spawn differe : Definition doit etre assignee AVANT BeginPlay (qui lit
	// Definition pour initialiser vie/vitesse), d'ou FinishSpawning plutot
	// qu'un SpawnActor direct.
	const FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);
	if (ACendreuxBase* Cendreux = GetWorld()->SpawnActorDeferred<ACendreuxBase>(Entry->CendreuxClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn))
	{
		Cendreux->Definition = Entry->Definition;
		Cendreux->FinishSpawning(SpawnTransform);
	}
}
