// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    auto PlayerTank = GetPlayerTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank!!!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(ControlledTank->GetName()));
        if(!PlayerTank)
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not find a player to aim at"));
        }
        else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *(PlayerTank->GetName()));
        }
    }

    //UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn)
    {
        return nullptr;
    }
    return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(GetPlayerTank())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *(GetPlayerTank()->GetActorLocation()).ToString());
        
        // Move towards the player
        // Aim at the player

        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

        // Fire if ready
    }

}

