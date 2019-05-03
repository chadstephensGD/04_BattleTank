// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{

	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (Throttle != 0) {
		FString Name = this->GetName();
		FString TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s: %s setting throttle to %f, force applied %s at location %s"), *TankName, *Name, Throttle,
			*ForceApplied.ToString(), *ForceLocation.ToString());
	}

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
