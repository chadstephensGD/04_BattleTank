// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, 
		StartLocation, HitLocation, LaunchSpeed, false, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

		/*auto OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s from %s, firing at %f"), *OurTankName,
			*AimDirection.ToString(),
			*StartLocation.ToString(),
			LaunchSpeed
		);*/
	} else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f no aiming solution found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// calc difference between current position and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("Delta rotator %s"), *DeltaRotator.ToString());

	Barrel->Elevate(5); // TODO remove static number
}

// TODO:rotate the turret to position the x/y
