// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessed tank: %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController has not possessed a tank"));
	}

	auto EnemyTank = GetPlayerTank();
	if (EnemyTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *(EnemyTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController has not found an enemy tank"));
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