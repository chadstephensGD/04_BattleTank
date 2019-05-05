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
		FString OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s Tracks not set correctly"), *OurTankName);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack && RightTrack) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	} else {
		FString OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s Tracks not set correctly"), *OurTankName);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankMovementIntention = MoveVelocity.GetSafeNormal();
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForwardVector, TankMovementIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForwardVector, TankMovementIntention).Z;
	IntendTurnRight(RightThrow);
	//FString OurTankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s requesting direct move at %s!"), *OurTankName, *AIMovementIntention.ToString());
}

