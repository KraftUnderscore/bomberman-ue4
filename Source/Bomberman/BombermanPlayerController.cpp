// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanPlayerController.h"

#include "BombermanCharacter.h"

void ABombermanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABombermanPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABombermanPlayerController::MoveRight);

	InputComponent->BindAction("SpecialAction", EInputEvent::IE_Released, this, &ABombermanPlayerController::SpecialAction);
}

void ABombermanPlayerController::MoveForward(float AxisValue)
{
	if (ABombermanCharacter* BombermanCharacter = GetPawn<ABombermanCharacter>())
	{
		BombermanCharacter->MoveForward(AxisValue);
	}
}

void ABombermanPlayerController::MoveRight(float AxisValue)
{
	if (ABombermanCharacter* BombermanCharacter = GetPawn<ABombermanCharacter>())
	{
		BombermanCharacter->MoveRight(AxisValue);
	}
}

void ABombermanPlayerController::SpecialAction()
{
	if (ABombermanCharacter* BombermanCharacter = GetPawn<ABombermanCharacter>())
	{
		BombermanCharacter->SpecialAction();
	}
}
