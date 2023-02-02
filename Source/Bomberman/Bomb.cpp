// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

ABomb::ABomb()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	MeshComponent->SetGenerateOverlapEvents(false);
}

void ABomb::SetLevel(const int32 NewLevel)
{
	Level = NewLevel;
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ExplosionTimer, this, &ABomb::Explode, TimeToExplode);
	}
}

void ABomb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}

	Super::EndPlay(EndPlayReason);
}

void ABomb::Explode()
{
	// Check all directions for hits
	const FVector StartPos = GetActorLocation();
	FVector EndPos1 = StartPos + (GetActorUpVector() * Level * 100.0f);
	FVector EndPos2 = StartPos - (GetActorUpVector() * Level * 100.0f);
	FVector EndPos3 = StartPos + (GetActorRightVector() * Level * 100.0f);
	FVector EndPos4 = StartPos - (GetActorRightVector() * Level * 100.0f);
	TArray<FVector> EndPositions = { EndPos1, EndPos2, EndPos3, EndPos4 };

	for (const FVector& EndPos : EndPositions)
	{
		TArray<FHitResult> HitResults;
		GetWorld()->LineTraceMultiByProfile(HitResults, StartPos, EndPos, FName("Bomb"));

		for (const FHitResult& HitResult : HitResults)
		{
			if (HitResult.Actor.IsValid())
			{
				HitResult.Actor.Get()->TakeDamage(1.0f, FDamageEvent(), GetInstigatorController(), this);
			}
		}
	}

	OnExplodeEvent.Execute();
	Destroy();
}
