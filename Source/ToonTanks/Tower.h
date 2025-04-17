// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	class ATank* tank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float fireRange = 300.0f;
	
	// timer handle for the FTimerManager.
	FTimerHandle FireRateTimerHandle;

	// Fire rate to how often we will call it.
	float FireRate{ 2.0f };

	// callback function.
	void CheckFireCondition();

	bool IsTankInRange();
};
