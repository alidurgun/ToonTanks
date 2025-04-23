// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// To handle death in game mode.
	void ActorDied(class AActor* DeadActor);

	// Blueprint Implementable Event for start game
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	// Blueprint Implementable Event for game over.
	// true => win
	// false => lost
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool status);

private:
	float StartDelay{ 3.f };
	void HandleGameStart();

	class AToonTanksPlayerController* PlayerController;

	// Get the number of target tower.
	uint32 GetTargetTower();

	// We gonna store our Target tower number here.
	uint32 TargetTower{ 0U };

protected:
// Called when the game starts or when spawned
	virtual void BeginPlay() override;
//
//private:
//	class ATank* Tank;
	
};
