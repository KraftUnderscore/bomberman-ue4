// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class BOMBERMAN_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	APowerUp();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp", meta = (AllowPrivateAccess = "true"))
	int32 PowerIncrease = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUp", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUp", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUp", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
