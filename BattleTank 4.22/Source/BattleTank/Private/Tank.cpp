// Copyright 2019 Chad Stephens, All rights Reserved

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

/*
FString OurTankName = this->GetName();
auto Time = GetWorld()->GetTimeSeconds();
UE_LOG(LogTemp, Warning, TEXT("%f: %s fires!"), Time, *OurTankName);
*/