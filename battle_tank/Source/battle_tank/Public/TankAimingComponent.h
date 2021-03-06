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
	Locked,
	OutOfAmmo
};

class UTankBarrel ;
class UTankTurret ;
class AProjectile ;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) ;

	void AimAt(FVector HitLocation) ;
	
	UFUNCTION(BlueprintCallable)
	void Fire() ;

	EFiringState GetFiringState() const ;

	UFUNCTION(BlueprintCallable)
	int GetRoundsLeft() const ;

protected:
	// Create an enum of type EFiring State, called Firing State and initialise it to Reloading
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading ;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override ;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override ;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving() ; 

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.0; // Sensible starting value of 10000m/s - lol 

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3 ;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<class AProjectile> ProjectileBluePrint ;  
	
	double LastFireTime = 0 ;

	FVector AimDirection ;

	int RoundsLeft = 5 ;

};
