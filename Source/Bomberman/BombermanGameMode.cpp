// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanGameMode.h"

#include "BombermanPlayerController.h"

ABombermanGameMode::ABombermanGameMode()
{
	PlayerControllerClass = ABombermanPlayerController::StaticClass();
}