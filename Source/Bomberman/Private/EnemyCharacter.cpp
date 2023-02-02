// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AddMovementInput(WalkDirection * GetActorForwardVector(), WalkSpeed);
	
	if (PrevLocation == GetActorLocation())
	{
		WalkDirection *= -1;
	}

	PrevLocation = GetActorLocation();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PrevLocation = GetActorLocation();
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CanBeDamaged() && DamageAmount > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage((uint64)this, 5.0f, FColor::Red, FString::Printf(TEXT("Got %i points!"), Score));
		Destroy();
		return DamageAmount;
	}

	return 0.0f;
}
