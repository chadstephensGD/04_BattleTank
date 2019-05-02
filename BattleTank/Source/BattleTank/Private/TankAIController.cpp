// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) // Called every frame
{
	Super::Tick(DeltaTime);
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* EnemyTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (EnemyTank) {
		// TODO: Turn/Move towards the player
		// Aim at the player
		ControlledTank->AimAt(EnemyTank->GetTargetLocation()); // course used GetActorLocation
		ControlledTank->Fire(); // TODO: limit firing rate
	}
}
