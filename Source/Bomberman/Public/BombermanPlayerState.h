// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BombermanPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void PowerUp(const int32 Increase);

	int32 GetBombPower() const { return BombsPower; }

private:
	int32 Score = 0;
	int32 BombsPower = 1;
};
