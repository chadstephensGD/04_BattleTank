// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ATank * GetControlledTank() const;
	void BeginPlay() override;
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector & OutHitLocation) const;
	bool GetAimDirection(FVector2D ScreenLocation, FVector& AimDirection) const;
	bool GetAimVectorHitLocation(FVector AimDirection, FVector& OutHitLocation) const;
};
