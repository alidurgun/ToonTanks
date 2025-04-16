// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	SpawnProjectile = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Projectile"));
	SpawnProjectile->SetupAttachment(TurretMesh);
}

// lookAtTarget is our end point.
void ABasePawn::rotateTurret(FVector lookAtTarget) {
	// target = end - start
	FVector target = lookAtTarget - TurretMesh->GetComponentLocation();

	// Because we only want to change yaw.
	FRotator targetRotation = FRotator(0.f, target.Rotation().Yaw, 0.f);

	// to set rotation of turret.
	FMath::RInterpTo(TurretMesh->GetComponentRotation(),
		targetRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		1.f);
}