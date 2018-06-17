// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
	Tank Track is used to set maximum driving force and to apply forces (to move) the tank
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// 
	UFUNCTION(BlueprintCallable, Category = Input )
	void SetThrottle(float Throttle);
	
	// This is the max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce =  20000000 ; // 40Ton tank accelerates at 1G acceleration

private:
	UTankTrack() ;

	virtual void BeginPlay() override ; 

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
