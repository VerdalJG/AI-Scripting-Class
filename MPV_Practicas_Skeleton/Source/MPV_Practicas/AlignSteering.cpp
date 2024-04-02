// Fill out your copyright notice in the Description page of Project Settings.


#include "AlignSteering.h"
#include "AICharacter.h"
#include "ExtensionFunctions.h"

SteeringValues AlignSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;

	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);
		float desiredAngle = ConvertTo360(character->GetParams().targetRotation);
		float currentRotation = ConvertTo360(character->rotation);
		float diff = ConvertTo180(desiredAngle - currentRotation);
		float desiredAngularVelocity;
		float desiredAngularAcceleration;

		if (fabs(diff) <= character->GetParams().angular_arrive_radius)
		{
			// Approaching target angle
			float lerpValue = 1 - fabs(diff) / character->GetParams().angular_arrive_radius;

			if (lerpValue > 0.99f)
			{
				lerpValue = 1;
			}

			desiredAngularVelocity = FMath::Lerp(character->GetParams().max_angular_velocity, 0.0f, lerpValue) * Sign(diff);

			diff = desiredAngularVelocity - character->angularVelocity;
		}

			// Away from target angle
			desiredAngularAcceleration = character->GetParams().max_angular_acceleration * Sign(diff);
			result.angularAcceleration = desiredAngularAcceleration;

	}

	return result;
}

AlignSteering::AlignSteering()
{
}

AlignSteering::~AlignSteering()
{
}
