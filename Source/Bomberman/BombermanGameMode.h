// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/PowerUp.h"
#include "BombermanGameMode.generated.h"

UCLASS(minimalapi)
class ABombermanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABombermanGameMode();

	virtual void StartPlay() override;

private:
	int32 EnemyCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomberman", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APowerUp> PowerUpClass;

	class AWall* WallWithPowerUp = nullptr;

	void BindEnemies();
	void SpawnPowerUp();

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
};



