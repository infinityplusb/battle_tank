#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"
#include "TankBarrel.generated.h"


UCLASS( meta=(BlueprintSpawnableComponent) , hidecategories = ("Collision"))
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    void Elevate(float DegressPerSecond);

private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 20 ; 

    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationPerSecond = 40 ; 

    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationPerSecond = 0 ; 
};