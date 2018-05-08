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
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override ; // the virtual here is redundant

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where 
	// the crosshair intersects the world
	void AimTowardsCrosshair();
};
