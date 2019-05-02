// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	/*if (Throttle != 0) {
		FString Name = this->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s setting throttle: %f"), *Name, Throttle);
	}*/

	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
