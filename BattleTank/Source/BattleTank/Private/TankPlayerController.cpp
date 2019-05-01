// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessed tank: %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has not possessed a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) // Called every frame
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Moves the tank barrel moving towards where the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) 
	{
		// TODO: tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
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
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult, StartLocation, EndLocation,
			ECollisionChannel::ECC_Visibility)) {
		// set hit locaiton
		OutHitLocation = HitResult.Location;
		return true;
	} else {
		OutHitLocation = FVector(0, 0, 0);
		return false;
	}
}
