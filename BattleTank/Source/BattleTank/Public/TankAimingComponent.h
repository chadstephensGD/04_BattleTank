// Copyright 2019 Chad Stephens, All rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declarations
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankBarrel * Barrel = nullptr;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadonly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Aiming;

private:
	UTankTurret * Turret = nullptr;

	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelAndTurretTowards(FVector AimDirection);
};
