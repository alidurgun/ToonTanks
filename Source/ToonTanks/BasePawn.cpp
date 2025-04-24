// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
// #include "DrawDebugHelpers.h"
#include "Projectilee.h"
#include "Engine/World.h"

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

void ABasePawn::HandleDestruction() {
	if (DeathParticle) {
		// Spawn the particle.
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}

	// Play death sound.
	if (DeathSound) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	
}

void ABasePawn::rotateTurret(FVector endPoint) {
	// target = end - start
	FVector target = endPoint - TurretMesh->GetComponentLocation();

	// Because we only want to change yaw.
	FRotator targetRotation = FRotator(0.f, target.Rotation().Yaw, 0.f);

	// to set rotation of turret.
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),
		targetRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		5.f)
		);
}

void ABasePawn::Fire() {
	// DrawDebugSphere(GetWorld(), SpawnProjectile->GetComponentLocation(), 30.0f, 10, FColor::Cyan, false, 3.0f);
	
	// To spawn actor with related BP class. We set the BP class in the
	// Base pawn's BP class. in the combat section for the ProjectileClass.
	auto projectile = GetWorld()->SpawnActor<AProjectilee>(ProjectileClass, SpawnProjectile->GetComponentLocation(), SpawnProjectile->GetComponentRotation());

	// we are setting it's owner to itself. We'll use it in on hit function.
	projectile->SetOwner(this);
}