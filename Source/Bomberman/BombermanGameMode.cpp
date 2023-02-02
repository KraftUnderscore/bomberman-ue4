// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "BombermanPlayerState.h"
#include "BombermanPlayerController.h"
#include "Wall.h"

ABombermanGameMode::ABombermanGameMode()
{
	PlayerControllerClass = ABombermanPlayerController::StaticClass();
	PlayerStateClass = ABombermanPlayerState::StaticClass();
}

void ABombermanGameMode::StartPlay()
{
	SpawnPowerUp();

	Super::StartPlay();
}

void ABombermanGameMode::SpawnPowerUp()
{
	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> AllWalls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWall::StaticClass(), AllWalls);

	const TArray<AActor*> DestructibleWalls = AllWalls.FilterByPredicate([](const AActor* Wall) { return Wall && Wall->CanBeDamaged(); });
	const int32 PowerUpIndex = FMath::RandRange(0, DestructibleWalls.Num() - 1);

	if (DestructibleWalls.IsValidIndex(PowerUpIndex))
	{
		WallWithPowerUp = Cast<AWall>(DestructibleWalls[PowerUpIndex]);

		const FTransform WallTransform = WallWithPowerUp->GetTransform();
		GetWorld()->SpawnActor(PowerUpClass, &WallTransform, FActorSpawnParameters());
	}
}
