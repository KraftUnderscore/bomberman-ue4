// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "Components/CapsuleComponent.h"

#include "BombermanPlayerState.h"
#include "../BombermanCharacter.h"

APowerUp::APowerUp()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetGenerateOverlapEvents(false);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCapsuleRadius(45.0f);
	CapsuleComponent->SetCapsuleHalfHeight(50.0f);
	CapsuleComponent->AttachTo(RootComponent);

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnBeginOverlap);
}

void APowerUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABombermanCharacter* Character = Cast<ABombermanCharacter>(OtherActor))
	{
		Character->PowerUp(PowerIncrease);
		Destroy();
	}
}

