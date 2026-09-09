#include "Pickups/EmberShard.h"
#include "Components/SphereComponent.h"
#include "Player/BraiseCharacter.h"
#include "Progression/XPComponent.h"
#include "Kismet/GameplayStatics.h"

AEmberShard::AEmberShard()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(30.f);
	CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEmberShard::OnOverlap);
	RootComponent = CollisionSphere;
}

void AEmberShard::BeginPlay()
{
	Super::BeginPlay();
	HomingTarget = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AEmberShard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HomingTarget.IsValid())
	{
		return;
	}

	const float Distance = FVector::Dist(GetActorLocation(), HomingTarget->GetActorLocation());
	if (Distance <= MagnetRadius)
	{
		const FVector Direction = (HomingTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		// Plus proche = attire plus vite -- rend le "dernier metre" satisfaisant.
		const float SpeedScale = FMath::GetMappedRangeValueClamped(FVector2D(0.f, MagnetRadius), FVector2D(1.5f, 0.3f), Distance);
		AddActorWorldOffset(Direction * MagnetSpeed * SpeedScale * DeltaTime, true);
	}
}

void AEmberShard::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABraiseCharacter* Character = Cast<ABraiseCharacter>(OtherActor))
	{
		Character->XPComponent->AddXP(XPValue);
		Destroy();
	}
}
