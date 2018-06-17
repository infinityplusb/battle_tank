// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "battle_tank.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    DriveTrack();
    ApplySidewaysForce() ;
    CurrentThrottle = 0 ;
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1) ; 
    // DriveTrack(float Throttle) ;
}

void UTankTrack::ApplySidewaysForce()
{
    // Workout the required acceleration this frame to correct
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity() );
    
    auto DeltaTime = GetWorld()->GetDeltaSeconds() ;
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector() ; 

    // Calculate and apply sideways
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()) ; 
    auto CorrectionForce = ( TankRoot->GetMass() * CorrectionAcceleration ) / 2 ; // Two Tracks

    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{
    // TODO clamp actual throttle value so player can't over-drive
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce ; 
    auto ForceLocation = GetComponentLocation() ;

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent() ) ;
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation) ;
}