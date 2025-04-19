// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// meta=(BlueprintSpawnableComponent) it allow us to add this component
// directly in blueprints.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHealth{ 100.f };
	float CurrentHealth{ 0.f };

	// game mode pointer
	class AToonTanksGameMode* ToonTaksGameMode;

	UFUNCTION()
	// DamagedActor => Actor that getting damage.
	// Damage => Amount of damage.
	// DamageType => type of damage (fire,poison, explosion etc.)
	// Instigator => responsible for damage. If player pawn caused damage
	// then it's the controller that's possessing that pawn. It can be null.
	// DamageCauser => Actual actor causing the damage, this would be the
	// projectile itself.
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		class AController* Instigator, AActor* DamageCauser);
};
