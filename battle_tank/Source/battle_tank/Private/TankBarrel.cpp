#include "battle_tank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds ;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange ; 

    auto NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees ) ;

    SetRelativeRotation(FRotator(NewElevation, 0, 0)) ;
}