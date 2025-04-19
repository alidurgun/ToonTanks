// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind the axis MoveForward function. W and S keys.
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    // Bind the axis Turn function. A and D keys.
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    // Bind the action Fire function. Mouse left click.
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(PlayerControllerRef)
    {
        FHitResult HitResult;

        // to get hit result from cursor.
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        
        // rotate turret with impact point.
        rotateTurret(HitResult.ImpactPoint);
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::HandleDestruction() {
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    DisableInput(PlayerControllerRef);
    PlayerControllerRef->bShowMouseCursor = false;
}

void ATank::Move(float value)
{
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = value * DeltaTime * TankSpeed;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}