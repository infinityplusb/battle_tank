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
    // UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit"))
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
//	Super::TickComponent() ;
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity() );
    
    // Workout the required acceleration this frame to correct
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector() ; 

    // Calculate and apply sideways
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()) ; 
    auto CorrectionForce = ( TankRoot->GetMass() * CorrectionAcceleration ) / 2 ; // Two Tracks

    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle:  %f"), *Name, Throttle);

    // TODO clamp actual throttle value so player can't over-drive
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce ; 
    auto ForceLocation = GetComponentLocation() ;

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent() ) ;
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation) ;
}

