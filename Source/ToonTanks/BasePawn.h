// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

// Forward decleration
class USoundBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// In case of death.
	virtual void HandleDestruction();

protected:
	// to rotate turret.
	void rotateTurret(FVector endPoint);

	// to fire projectile.
	void Fire();

	// Particle that will be spawn on death of actor.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticle;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectilee> ProjectileClass;

	// Sound effects
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
};
