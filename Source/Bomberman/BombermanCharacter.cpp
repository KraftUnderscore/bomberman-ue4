// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include <BombermanPlayerState.h>

ABombermanCharacter::ABombermanCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 270.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PrimaryActorTick.bCanEverTick = false;
}

void ABombermanCharacter::MoveForward(float AxisValue)
{
	MoveCharacter(AxisValue, EAxis::X);
}

void ABombermanCharacter::MoveRight(float AxisValue)
{
	MoveCharacter(AxisValue, EAxis::Y);
}

void ABombermanCharacter::SpecialAction()
{
	if (UWorld* World = GetWorld())
	{
		const FTransform BombTransform = GetTransform();
		AActor* Actor = World->SpawnActor(BombClass, &BombTransform, FActorSpawnParameters());
		ABomb* Bomb = Cast<ABomb>(Actor);

		if (ABombermanPlayerState* PS = GetPlayerState<ABombermanPlayerState>())
		{
			Bomb->SetLevel(PS->GetBombPower());
		}
	}
}

void ABombermanCharacter::MoveCharacter(float AxisValue, EAxis::Type Axis)
{
	if (FMath::IsNearlyZero(AxisValue))
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(Axis);
	AddMovementInput(Direction, AxisValue);
}
