// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading, 
	Aiming, 
	Locked
};

class UTankBarrel ;
class UTankTurret ;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) ;

//	void SetBarrelReference(UTankBarrel* BarrelToSet);
//	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation) ;
	
protected:
	// Create an enum of type EFiring State, called Firing State and initialise it to Reloading
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading ;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.0; // Sensible starting value of 10000m/s - lol 

	void MoveBarrelTowards(FVector AimDirection);
};
