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

    FVector OutHitLocation; // Out parameter
    if( GetSightRayHitLocation(OutHitLocation) ) // Has "side-effect", is going to line trace
    {
        // UE_LOG(LogTemp, Warning, TEXT("Hitting Location: %s"), *OutHitLocation.ToString());
    }
}

// return OutHitLocation
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // find the crosshair position
    int32 ViewportSizeX, ViewportSizeY ;
    GetViewportSize(ViewportSizeX, ViewportSizeY); 

    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    // UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *(ScreenLocation.ToString()));

    // De- project the screen position of the crosshair to the world direction
    // Line Trace along that look direction and see what we hit (up to a max range)
    // OutHitLocation = FVector(1.0);
    return true;


    //const FVector Start = GetFocalLocation();

    //const FVector End 
    //FHitResult HitData(ForceInit);

    //if( UMyStaticFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData) )
    //{
    //    if(HitData.Get)
    //}
}