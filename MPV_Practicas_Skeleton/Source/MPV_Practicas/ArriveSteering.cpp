// Fill out your copyright notice in the Description page of Project Settings.


#include "ArriveSteering.h"
#include "AICharacter.h"
#include "ExtensionFunctions.h"

SteeringValues ArriveSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;
	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);
		FVector actorLocation = actor->GetActorLocation();
		FVector desiredVelocity = target.targetPosition - actorLocation;
		FVector distance = desiredVelocity;
		

		if (distance.Length() < character->GetParams().dest_radius)
		{
			float lerpValue = 1 - (distance.Length() / character->GetParams().dest_radius);
			if (lerpValue > 0.99)
			{
				lerpValue = 1;
			}
			FVector startVelocity = desiredVelocity.GetSafeNormal() * character->GetParams().max_velocity;
			FVector endVelocity = FVector::Zero();
			desiredVelocity = LerpVector(startVelocity, endVelocity, lerpValue);
			FVector desiredAcceleration = desiredVelocity - character->velocity;
			desiredAcceleration = desiredAcceleration.GetSafeNormal() * character->GetParams().max_acceleration;
			result.linearAcceleration = desiredAcceleration;
		}

		else
		{
			desiredVelocity = desiredVelocity.GetSafeNormal() * character->GetParams().max_velocity;
			FVector desiredAcceleration = desiredVelocity - character->velocity;
			desiredAcceleration = desiredAcceleration.GetSafeNormal() * character->GetParams().max_acceleration;
			result.linearAcceleration = desiredAcceleration;
		}
	}
	return result;
}

ArriveSteering::ArriveSteering()
{
}

ArriveSteering::~ArriveSteering()
{
}


