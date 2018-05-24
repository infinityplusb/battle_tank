#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"
#include "TankBarrel.generated.h"


UCLASS()
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    void Elevate(float DegressPerSecond);

private:
    UPROPERTY(EditAnywhere)
    float MaxDegreesPerSecond = 20 ; // Sensible default
};