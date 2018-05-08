// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank!!!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
    }

    //UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

// Tick
// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshair();    
//    UE_LOG(LogTemp, Warning, TEXT("PlayerController tick!"));

}


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
    if (!GetControlledTank()) { return; }

    // Get World location of linetrace through crosshair
    // if it hits the landscape
        // tell the tank to aim at that point
}