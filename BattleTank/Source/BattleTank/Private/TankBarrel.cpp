// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// given max elevation speed and frame time
	// change the tilt of the barrel the correct amount this frame
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f called elevate in barrel component %f"), Time, RelativeSpeed);
}