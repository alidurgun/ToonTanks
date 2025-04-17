// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectilee.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectilee::AProjectilee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// We set it to false because we don't need tick for this component!
	PrimaryActorTick.bCanEverTick = false;

	// Create a ustatic mesh component for projectile.
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	
	// Then set it to root component.
	RootComponent = ProjectileMesh;

	// To create projectile movement component.
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	// Initial and max speed values for the movement component.
	MovementComponent->InitialSpeed = 1300.0f;
	MovementComponent->MaxSpeed = 1300.0f;
}

// Called when the game starts or when spawned
void AProjectilee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectilee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

