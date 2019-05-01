// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessed tank: %s"), *(ControlledTank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController has not possessed a tank"));
	}

}

void ATankAIController::Tick(float DeltaTime) // Called every frame
{
	Super::Tick(DeltaTime);

	auto EnemyTank = GetPlayerTank();
	if (EnemyTank) {
		// TODO: Turn/Move towards the player
		// Aim at the player
		GetControlledTank()->AimAt(EnemyTank->GetTargetLocation()); // course used GetActorLocation
		// TODO: Fire when ready
	}
}


ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}