// Copyright 2019 Chad Stephens, All rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// setup on death delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

// Defines the actual tanks for the game
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	// variables
	FTankDelegate OnDeath;
	// functions
	UFUNCTION(BlueprintPure, Category = "Statistics")
	float GetHealthPercent() const; // Return current health as a percentage of starting health between 0 and 1
	virtual void BeginPlay() override;

private:
	// variables
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxHealth = 100.0;
	UPROPERTY(VisibleAnywhere, Category = "Statistics")
	float CurrentHealth;

	// functions
	ATank(); // constructor
	// TakeDamage is automatically called by UE when struck
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
