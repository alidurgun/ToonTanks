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

	// Blueprint Implementable Event
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:
	float StartDelay{ 3.f };
	void HandleGameStart();

	class AToonTanksPlayerController* PlayerController;

protected:
// Called when the game starts or when spawned
	virtual void BeginPlay() override;
//
//private:
//	class ATank* Tank;
	
};
