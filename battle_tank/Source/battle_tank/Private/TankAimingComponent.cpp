// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, 
		OutLaunchVelocity,
		StartLocation, 
		HitLocation, 
		LaunchSpeed,
		false, 
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (ensure(bHaveAimSolution))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		
		auto Time = GetWorld()->GetTimeSeconds();
    	// UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution found"), Time);
		
		MoveBarrelTowards(AimDirection);
	}
	else 
	{
		// auto Time = GetWorld()->GetTimeSeconds();
    	// UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator ;

	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
}