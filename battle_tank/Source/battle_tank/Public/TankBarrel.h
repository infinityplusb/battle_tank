#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"
#include "TankBarrel.generated.h"


UCLASS( meta=(BlueprintSpawnableComponent) , hidecategories = ("Collision"))
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    // -1 is max downward movement, and +1 is max upward movement
    void Elevate(float RelativeSpeed);

private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 20 ; 

    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees = 40 ; 

    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees = 0 ; 
};