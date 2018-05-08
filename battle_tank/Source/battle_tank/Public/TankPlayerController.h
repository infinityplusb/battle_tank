// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public: 
	virtual void BeginPlay() override ; // the virtual here is redundant

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere) 
	float CrossHairXLocation = 0.5 ;

	UPROPERTY(EditAnywhere) 
    float CrossHairYLocation = 0.33333 ;

	ATank* GetControlledTank() const;
	
	
	// Start the tank moving the barrel so that a shot would hit where 
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT Parameter, true if hit landscape
	bool GetSightRayHitLocation( FVector& OutHitLocation) const;
};
