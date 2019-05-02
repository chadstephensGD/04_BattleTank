// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	} else {
		UE_LOG(LogTemp, Error, TEXT("Tracks not set correctly"));
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(-Throw);
		RightTrack->SetThrottle(Throw);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Tracks not set correctly"));
	}
}
