// Copyright 2019 Chad Stephens, All rights Reserved

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringStatus::Reloading;
	} else if (IsBarrelMoving()) {
		FiringState = EFiringStatus::Aiming;
	} else {
		FiringState = EFiringStatus::Locked;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, 
		StartLocation, HitLocation, LaunchSpeed, false, 0,0,ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelAndTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelAndTurretTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Error, TEXT("Barrel is not connected in Move Function")); return; }
	if (!ensure(Turret)) { UE_LOG(LogTemp, Error, TEXT("Turret is not connected in Move Function")); return; }

	// calc difference between current position and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	// rotate the turret to position the x/y
	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	
	return (!BarrelForward.Equals(AimDirection, 0.01));
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringStatus::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		// Spawn the projectile at the end of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		// Set the projectfile moving
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
/*auto OurTankName = GetOwner()->GetName();
UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s from %s, firing at %f"), *OurTankName,
*AimDirection.ToString(),
*StartLocation.ToString(),
LaunchSpeed
);*/