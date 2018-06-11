// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn()) ;

    if(PlayerTank)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *(GetPlayerTank()->GetActorLocation()).ToString());
        
        // Move towards the player
        // Aim at the player

        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        // Fire if ready
        ControlledTank->Fire() ; // todo limit firing rate
    }

}

