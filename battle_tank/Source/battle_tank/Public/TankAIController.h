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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// public: this was public ... 
private:
	virtual void BeginPlay() override ; // the virtual here is redundant
	
	ATank* GetControlledTank() const;
	
	ATank* GetPlayerTank() const;
};
