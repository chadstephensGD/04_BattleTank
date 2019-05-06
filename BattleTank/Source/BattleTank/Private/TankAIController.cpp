// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime) // Called every frame
{
	Super::Tick(DeltaTime);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
	auto EnemyTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(EnemyTank)) {
		// Turn/Move towards the player
		MoveToActor(EnemyTank, AcceptanceRadius); // TODO check radius is in cm
		// Aim at the player
		AimingComponent->AimAt(EnemyTank->GetTargetLocation()); // course used GetActorLocation
		AimingComponent->Fire();
	} else {
		FString TankName = this->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s did not detect enemy tank"), *TankName);
	}
}
