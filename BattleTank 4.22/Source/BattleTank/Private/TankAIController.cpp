// Copyright 2019 Chad Stephens, All rights Reserved

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// subscribe to tank's OnDeath
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime) // Called every frame
{
	Super::Tick(DeltaTime);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
	auto EnemyTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (EnemyTank) {
		// Turn/Move towards the player
		MoveToActor(EnemyTank, AcceptanceRadius); // TODO check radius is in cm
		// Aim at the player
		AimingComponent->AimAt(EnemyTank->GetTargetLocation()); // course used GetActorLocation

		// if locked only
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
