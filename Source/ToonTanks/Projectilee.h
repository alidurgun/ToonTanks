// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectilee.generated.h"

class UProjectileMovementComponent;

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
