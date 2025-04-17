// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    // add additional components for the tank.
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// handle input section.
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // call the base function.
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // bind MoveForward in axis mappings to Move function.
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    // bind Turn in axis mappings to Turn function.
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(PlayerControllerRef)
    {
        FHitResult HitResult;

        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
        // to get hit result from cursor position.
        rotateTurret(HitResult.ImpactPoint); // to rotate turret.
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();
    // to rotate turret with mouse.
    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float value)
{
    // to make it frame independent.
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    // initialize 0 vector.
    FVector DeltaLocation = FVector::ZeroVector;

    // x is refers to local forward vector.
    DeltaLocation.X = value * DeltaTime * TankSpeed;

    // to move actor.
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float value)
{
    // 0 vector rotation value.
    FRotator DeltaRotation = FRotator::ZeroRotator;
    
    // to turn turret we use yaw.
    DeltaRotation.Yaw = value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    
    // to turn turret use AddActorLocalRotation function.
    AddActorLocalRotation(DeltaRotation, true);
}