// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "battle_tank.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet ;
    RightTrack = RightTrackToSet ;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super as we're replacing the functionality
    // auto TankName = GetOwner()->GetName();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    auto ForwardThrowRequired = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrowRequired);

    auto TurnRightRequired = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(TurnRightRequired);
    // UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString )
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    // UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
    if(!ensure(LeftTrack && RightTrack)) {return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw); 
}
   
void UTankMovementComponent::IntendTurnRight(float Throw)
{
    // UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
    if(!ensure(LeftTrack && RightTrack)) {return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

