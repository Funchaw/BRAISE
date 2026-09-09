#include "Core/BraiseGameMode.h"
#include "Player/BraiseCharacter.h"

ABraiseGameMode::ABraiseGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ABraiseCharacter::StaticClass();
}

void ABraiseGameMode::BeginPlay()
{
	Super::BeginPlay();
	RunElapsedSeconds = 0.f;
	CendreuxDefeated = 0;
}

void ABraiseGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunElapsedSeconds += DeltaTime;
}

void ABraiseGameMode::NotifyCendreuxDefeated()
{
	CendreuxDefeated++;
}

void ABraiseGameMode::EndRun()
{
	OnRunEnded.Broadcast();
}
