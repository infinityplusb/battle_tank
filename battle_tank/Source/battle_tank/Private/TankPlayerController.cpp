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
        GetControlledTank()->AimAt(OutHitLocation);
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
    FVector LookDirection ;
    //FHitResult Outhit ; 
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *(LookDirection.ToString()));
        // Line Trace along that look direction and see what we hit (up to a max range)
        GetLookVectorHitLocation(LookDirection, OutHitLocation) ;
        //UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *(LookDirection.ToString()));
    }
    
    // OutHitLocation = FVector(1.0);
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection ) const 
{
    // De- project the screen position of the crosshair to the world direction
    FVector CameraWorldLocation; // To be discarded 
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection ) ;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    // ECC_Visibility channel
    FHitResult HitResult ;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + ( LookDirection * LineTraceRange ) ;

    if ( GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility) )
    {
        OutHitLocation = HitResult.Location ;
        return true ;
    }
    OutHitLocation = FVector(0);
    return false ;
    
}