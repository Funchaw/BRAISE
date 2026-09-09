#include "Player/BraiseCharacter.h"
#include "Player/HeatGaugeComponent.h"
#include "Progression/XPComponent.h"
#include "Weapons/WeaponComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABraiseCharacter::ABraiseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Vue du dessus / isometrique legere : coherent avec une zone semi-ouverte
	// de type survivors-like plutot qu'un defilement horizontal de shmup pur.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	HeatGauge = CreateDefaultSubobject<UHeatGaugeComponent>(TEXT("HeatGauge"));
	XPComponent = CreateDefaultSubobject<UXPComponent>(TEXT("XPComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
}

void ABraiseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ABraiseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABraiseCharacter::HandleMove);
		}
	}
}

void ABraiseCharacter::HandleMove(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (!Controller)
	{
		return;
	}

	// Deplacement libre sur le plan XY, sans lien a la rotation camera --
	// coherent avec une camera fixe/isometrique de zone semi-ouverte.
	AddMovementInput(FVector::ForwardVector, MoveInput.Y);
	AddMovementInput(FVector::RightVector, MoveInput.X);
}
