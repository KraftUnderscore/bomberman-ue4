// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

#include "Components/CapsuleComponent.h"

#include "BombermanCharacter.h"
#include "BombermanPlayerState.h"

ABomb::ABomb()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	MeshComponent->SetGenerateOverlapEvents(false);

	HorizontalCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("HorCapsule");
	HorizontalCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HorizontalCapsuleComp->SetCapsuleRadius(45.0f);
	HorizontalCapsuleComp->SetCapsuleHalfHeight(CapsuleDefaultHeight);
	HorizontalCapsuleComp->SetRelativeRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
	HorizontalCapsuleComp->AttachTo(RootComponent);

	VerticalCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("VerCapsule");
	VerticalCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	VerticalCapsuleComp->SetCapsuleRadius(45.0f);
	VerticalCapsuleComp->SetCapsuleHalfHeight(CapsuleDefaultHeight);
	VerticalCapsuleComp->SetRelativeRotation(FQuat(FRotator(90.0f, 90.0f, 0.0f)));
	VerticalCapsuleComp->AttachTo(RootComponent);
}

void ABomb::SetLevel(const int32 NewLevel)
{
	Level = NewLevel;

	HorizontalCapsuleComp->SetCapsuleHalfHeight(CapsuleDefaultHeight * (1 + Level));
	VerticalCapsuleComp->SetCapsuleHalfHeight(CapsuleDefaultHeight * (1 + Level));
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	if (ABombermanCharacter* Character = GetInstigator<ABombermanCharacter>())
	{
		if (ABombermanPlayerState* PS = Character->GetPlayerState<ABombermanPlayerState>())
		{
			SetLevel(PS->GetBombPower());
		}
	}
	
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
	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor)
		{
			Actor->TakeDamage(1.0f, FDamageEvent(), GetInstigatorController(), this);
		}
	}

	Destroy();
}
