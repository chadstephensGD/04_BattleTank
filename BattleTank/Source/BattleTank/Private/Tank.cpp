// Copyright 2019 Chad Stephens, All rights Reserved

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
	FString OurTankName = this->GetName();
	UE_LOG(LogTemp, Warning, TEXT("[%s] Caris: cpp constructor"), *OurTankName);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() 
{
	Super::BeginPlay();
	FString OurTankName = this->GetName();
	UE_LOG(LogTemp, Warning, TEXT("[%s] Caris: cpp begin play"), *OurTankName);
}

/* ----- SETUP FUNCTIONS ------ */
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/* ----- ACTION FUNCTIONS ------ */
void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!TankAimingComponent) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (TankAimingComponent->Barrel && isReloaded)
	{
		// Spawn the projectile at the end of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, TankAimingComponent->Barrel->GetSocketLocation(FName("Projectile")), TankAimingComponent->Barrel->GetSocketRotation(FName("Projectile")));
		// Set the projectfile moving
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

/*
FString OurTankName = this->GetName();
auto Time = GetWorld()->GetTimeSeconds();
UE_LOG(LogTemp, Warning, TEXT("%f: %s fires!"), Time, *OurTankName);
*/