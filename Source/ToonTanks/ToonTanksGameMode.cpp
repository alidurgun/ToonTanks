// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Delegates/DelegateSignatureImpl.inl"

void AToonTanksGameMode::ActorDied(AActor* DeadActor) {

	if (DeadActor == nullptr) return;
	Cast<ABasePawn>(DeadActor)->HandleDestruction();

	if (Cast<ATank>(DeadActor)) {
		// If dead actor is tank then we lost the game.
		GameOver(false);
	}
	else if (Cast<ATower>(DeadActor)) {
		--TargetTower;
		if (TargetTower == 0) {
			// If all of the target tower is dead then we won the game.
			GameOver(true);
		}
	}
	/*return;

	if (Tank == DeadActor) Tank->HandleDestruction();

	else if (ATower* destroyedTower = Cast<ATower>(DeadActor)) destroyedTower->HandleDestruction();*/
}

// Handle game start function to count down a timer.
void AToonTanksGameMode::HandleGameStart() {
	// call the event.
	StartGame();

	// Get the player controller.
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	if (PlayerController)
	{
		// disable the input for the beginning.
		PlayerController->SetPlayerEnabledState(false);

		// Create a FTimerHandle for countdown.
		FTimerHandle PlayerTimerHandle;

		// create FTimerDelegate object. It will call our callback function
		// when the timer is fired up.
		FTimerDelegate PlayerEnableTimerDelegate;

		// @param PlayerController => our player controller.
		// @param callback function => this callback function will be called.
		// @param true => input parameter for the callback function.
		PlayerEnableTimerDelegate.BindUObject(
			PlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		// Set the timer in here.
		// @param PlayerTimerHandle => FTimerHandle object that we created!
		// @param PlayerEnableTimerDelegate => delegate function with callback.
		// @param StartDelay => delay time in float.
		// @param false => to make it one time timer. If we set it true it will
		// continue in the loop.
		GetWorldTimerManager().SetTimer(PlayerTimerHandle,
			PlayerEnableTimerDelegate, StartDelay, false
		);
	}
}

void AToonTanksGameMode::BeginPlay() {
	TargetTower = GetTargetTower();
	HandleGameStart();
}

uint32 AToonTanksGameMode::GetTargetTower() {
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}