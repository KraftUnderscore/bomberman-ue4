// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateOptionalDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->AttachTo(RootComponent);
}

float AWall::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CanBeDamaged() && DamageAmount > 0.0f)
	{
		Destroy();
		return DamageAmount;
	}

	return 0.0f;
}
