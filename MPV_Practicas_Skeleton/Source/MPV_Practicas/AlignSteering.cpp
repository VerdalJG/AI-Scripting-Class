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

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("desiredAng: %f"), desiredAngle));
		}

		float desiredAngularVelocity = (desiredAngle - character->rotation) * character->GetParams().max_angular_velocity;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("desiredVel: %f"), desiredAngularVelocity));
		}

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
