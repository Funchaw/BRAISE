#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BraiseGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRunEnded);

/**
 * GameMode du prototype : une seule zone/run (voir
 * docs/02-prototype/prototype-ue5.md). Le decoupage par biome et la
 * progression meta (Braisier, Codex) s'ajoutent en vertical slice sans
 * changer cette base.
 */
UCLASS()
class BRAISE_API ABraiseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABraiseGameMode();

	UPROPERTY(BlueprintReadOnly, Category = "Braise|Run")
	float RunElapsedSeconds = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Braise|Run")
	int32 CendreuxDefeated = 0;

	UPROPERTY(BlueprintAssignable, Category = "Braise|Run")
	FOnRunEnded OnRunEnded;

	UFUNCTION(BlueprintCallable, Category = "Braise|Run")
	void NotifyCendreuxDefeated();

	UFUNCTION(BlueprintCallable, Category = "Braise|Run")
	void EndRun();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
