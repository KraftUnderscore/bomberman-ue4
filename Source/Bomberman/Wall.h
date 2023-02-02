// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class BOMBERMAN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

	void StartPowerUpAnimation();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	bool bAnimate = false;
	bool bHoverUp = true;

	FVector StartingLocation;
	FVector EndLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
	float HoverAmount = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
	float HoverSpeed = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
	int32 Score = 400;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

};
