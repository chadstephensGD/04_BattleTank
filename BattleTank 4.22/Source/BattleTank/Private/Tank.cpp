// Copyright 2019 Chad Stephens, All rights Reserved

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float  ATank::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

float ATank::TakeDamage(float DamageAmount,	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		// TODO: created tank destruction routine
		FString OurTankName = this->GetName();
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

/*
FString OurTankName = this->GetName();
auto Time = GetWorld()->GetTimeSeconds();
UE_LOG(LogTemp, Warning, TEXT("%f: %s fires!"), Time, *OurTankName);
*/