// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent ;
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

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimCompRef) ;

private:

	UPROPERTY(EditAnywhere) 
	float CrossHairXLocation = 0.5 ;

	UPROPERTY(EditAnywhere) 
    float CrossHairYLocation = 0.33333 ;


	UPROPERTY(EditAnywhere) 
    float LineTraceRange = 1000000.0 ;
	
	// Start the tank moving the barrel so that a shot would hit where 
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT Parameter, true if hit landscape
	bool GetSightRayHitLocation( FVector& OutHitLocation ) const;

	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const ;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const ;
};
