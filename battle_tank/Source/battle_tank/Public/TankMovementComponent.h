// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack ; 
/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// Throw is how far back the controller is moved
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw) ;
	
	// Throw is how far back the controller is moved
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw) ;
	
	// TODO check best protection
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr ; 	
	UTankTrack* RightTrack = nullptr ;
};
