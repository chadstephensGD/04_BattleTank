// Copyright 2019 Chad Stephens, All rights Reserved

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount,	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	// TODO: Add health bars
	if (CurrentHealth <= 0) {
		// TODO: created tank destruction routine
		FString OurTankName = this->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s: destroyed"), *OurTankName);
	}

	return DamageToApply;
}

/*
FString OurTankName = this->GetName();
auto Time = GetWorld()->GetTimeSeconds();
UE_LOG(LogTemp, Warning, TEXT("%f: %s fires!"), Time, *OurTankName);
*/