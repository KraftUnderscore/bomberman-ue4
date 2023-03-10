// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Bomb.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombermanCharacter.generated.h"

UCLASS(Blueprintable)
class ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABombermanCharacter();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void SpecialAction();
	void PowerUp(const int32 Increase);

private:
	int32 BombCount = 1;
	int32 BombsPower = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomberman", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABomb> BombClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	void MoveCharacter(float AxisValue, EAxis::Type Axis);

	void ReplenishBomb();
};