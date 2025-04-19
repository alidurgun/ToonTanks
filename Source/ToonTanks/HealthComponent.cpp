// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Controller.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// set Current health to max health.
	CurrentHealth = MaxHealth;
	
	// Bind the damage function.
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	// Set game mode.
	ToonTaksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser) {
	// UE_LOG(LogTemp, Warning, TEXT("Damage received"));
	if (Damage <= 0.f) return;

	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.f && ToonTaksGameMode) {
		ToonTaksGameMode->ActorDied(DamagedActor);
	}
	// UE_LOG(LogTemp, Warning, TEXT("Current healt is = %f"), CurrentHealth);
}

