// Copyright 2019 Chad Stephens, All rights Reserved

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (ensure(LeftTrack && RightTrack)) {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	} else {
		FString OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s Tracks not set correctly"), *OurTankName);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (ensure(LeftTrack && RightTrack)) {
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

