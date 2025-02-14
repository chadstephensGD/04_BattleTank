// Copyright 2019 Chad Stephens, All rights Reserved

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// subscribe to tank's OnDeath
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime) // Called every frame
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// Moves the tank barrel moving towards where the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair
// returns true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// find the crosshair position, in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

	// de-project the screen position of the crosshair to a world direction
	FVector AimDirection;
	if (GetAimDirection(ScreenLocation, AimDirection)) {
		return (GetAimVectorHitLocation(AimDirection, OutHitLocation));
	}
	return false;
}

bool ATankPlayerController::GetAimDirection(FVector2D ScreenLocation, FVector& AimDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, AimDirection);
}

bool ATankPlayerController::GetAimVectorHitLocation(FVector AimDirection, FVector& OutHitLocation) const
{
	// line-trace along the AimDirection and see what we hit (up to a max range)
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + AimDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,ECollisionChannel::ECC_Camera)) {
		// set hit locaiton
		OutHitLocation = HitResult.Location;
		return true;
	} else {
		OutHitLocation = FVector(0, 0, 0);
		return false;
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}
