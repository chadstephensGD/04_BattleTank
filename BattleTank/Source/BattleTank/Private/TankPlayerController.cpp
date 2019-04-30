// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

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

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
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
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		// TODO: tell controlled tank to aim at this point
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
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

	// de-project the screen position of the crosshair to a world direction
	// line-trace along that look direction and see what we hit (up to a max range)
	OutHitLocation = FVector(1.0);
	return true;
	/// Line-trace (ray-cast) out to reach distance
	//FHitResult HitResult;
	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	//GetWorld()->LineTraceSingleByObjectType(
	//	OUT HitResult,
	//	GetReachLineStart(),
	//	GetReachLineEnd(),
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	//	TraceParameters
	//);
	//return HitResult;
}