// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor) {

	if (DeadActor == nullptr) return;
	Cast<ABasePawn>(DeadActor)->HandleDestruction();
	/*return;

	if (Tank == DeadActor) Tank->HandleDestruction();

	else if (ATower* destroyedTower = Cast<ATower>(DeadActor)) destroyedTower->HandleDestruction();*/
}

//void AToonTanksGameMode::BeginPlay() {
//	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
//}