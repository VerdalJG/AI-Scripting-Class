// Fill out your copyright notice in the Description page of Project Settings.


#include "AlignSteering.h"
#include "AICharacter.h"

SteeringValues AlignSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;

	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);
		float desiredAngle = character->GetParams().targetRotation;
		float desiredAngularVelocity = (desiredAngle - character->GetActorRotation().Pitch) * character->GetParams().max_angular_velocity;
		float desiredAngularAcceleration = desiredAngularVelocity - character->angularVelocity;
		result.angularAcceleration = desiredAngularAcceleration * character->GetParams().max_angular_acceleration;
	}

	return result;
}

AlignSteering::AlignSteering()
{
}

AlignSteering::~AlignSteering()
{
}
