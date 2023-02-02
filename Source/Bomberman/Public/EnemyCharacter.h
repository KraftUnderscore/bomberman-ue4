// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class BOMBERMAN_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	int32 WalkDirection = 1;

	FVector PrevLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 0.25;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	int32 Score = 1000;

	float DirectionSwitchCooldown = 0.0f;
};
