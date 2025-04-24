// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

bool ATower::IsTankInRange() {
	// to prevent crash.
	if (tank) {
		// find the distance to the Tank
		float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());

		// Check to see if the Tank is in range
		if (distance <= fireRange) {
			return true;
		}
	}
	return false;
}

void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	// to prevent crash.
	if (IsTankInRange()) {
		// If we have a tank in range so we need to rotate the turret.
		rotateTurret(tank->GetActorLocation());
	}
}

void ATower::BeginPlay() {
	Super::BeginPlay();

	// 0 is our tank's gameplay id. So it'll be always 0 for singleplayer games.
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition() {
	if (IsTankInRange() && tank->isTankAlive()) {
		// If we have a tank in range then fire.
		Fire();
	}
}