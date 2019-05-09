// Copyright 2019 Chad Stephens, All rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Sets up the AI for the game
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// Variables
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 7000;

	// Functions
	virtual void SetPawn(APawn* InPawn) override; // called on posession
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnTankDeath();
};
