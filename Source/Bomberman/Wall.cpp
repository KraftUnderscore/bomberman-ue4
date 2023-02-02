// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateOptionalDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->AttachTo(RootComponent);
}

void AWall::StartPowerUpAnimation()
{
	GEngine->AddOnScreenDebugMessage((uint64)this, 5.0f, FColor::Blue, FString::Printf(TEXT("Find the powerup!"), Score));
	Destroy();
}

float AWall::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CanBeDamaged() && DamageAmount > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage((uint64)this, 5.0f, FColor::Blue, FString::Printf(TEXT("Got %i points!"), Score));
		Destroy();
		return DamageAmount;
	}

	return 0.0f;
}
