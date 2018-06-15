// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    }
}

// Tick Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshair();    
}

void ATankPlayerController::AimTowardsCrosshair() 
{
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) { return ; }

    FVector OutHitLocation; // Out parameter
    if( GetSightRayHitLocation(OutHitLocation) ) // Has "side-effect", is going to line trace
    {
        AimingComponent->AimAt(OutHitLocation);
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
        return GetLookVectorHitLocation(LookDirection, OutHitLocation) ;
        //UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *(LookDirection.ToString()));
    }
    
    // OutHitLocation = FVector(1.0);
    return false;
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

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetPawn());

    if (ensure(GetWorld()->LineTraceSingleByChannel(
        HitResult, 
        StartLocation, 
        EndLocation, 
        ECollisionChannel::ECC_Visibility,
        Params)) 
    )
    {
        OutHitLocation = HitResult.Location ;
        return true ;
    }
    OutHitLocation = FVector(0);
    return false ;
    
}