// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectilee.generated.h"

// Forward Decleration
class UProjectileMovementComponent;
class USoundBase;

UCLASS()
class TOONTANKS_API AProjectilee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectilee();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float damageValue{ 50.f };

	// To create a explosion effect.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	// It's component because we are gonna attach it to our particle system
	// So it will follow our particle as long as it's valid particle.
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;

	// Sound Effects:
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UFUNCTION()
	// hitComp => This is the component that doing the hit.
	// otherActor => Actor that get hit.
	// otherComp => other component that got hit.
	// NormalImpulse => direction and the magnitude of the impulse.
	// Hit => Has more information about the hit.
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor,
		UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
