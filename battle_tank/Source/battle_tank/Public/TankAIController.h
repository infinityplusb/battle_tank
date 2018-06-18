// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank ;

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:	

protected:
	// How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 8000 ;

private:
	virtual void BeginPlay() override ; // the virtual here is redundant
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
