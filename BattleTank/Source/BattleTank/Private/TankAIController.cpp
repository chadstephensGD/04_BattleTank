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
	FString EnemyName = EnemyTank->GetName();
	FString TankName = this->GetName();

	if (ensure(EnemyTank)) {
		// Turn/Move towards the player
		MoveToActor(EnemyTank, AcceptanceRadius); // TODO check radius is in cm
		// Aim at the player
		ControlledTank->AimAt(EnemyTank->GetTargetLocation()); // course used GetActorLocation
		ControlledTank->Fire();
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s did not detect enemy tank"), *TankName);
	}
}
