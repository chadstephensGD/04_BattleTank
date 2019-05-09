// Copyright 2019 Chad Stephens, All rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Defines the actual tanks for the game
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// variables
	UPROPERTY(VisibleAnywhere, Category = "Statistics")
	float CurrentHealth = 100.0;

	// functions
	ATank(); // constructor
	virtual float TakeDamage(float DamageAmount,	struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
