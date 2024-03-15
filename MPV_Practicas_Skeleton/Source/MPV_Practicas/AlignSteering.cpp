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
		float desiredAngle = ExtensionFunctions::ConvertTo360(character->GetParams().targetRotation);
		float currentRotation = ExtensionFunctions::ConvertTo360(character->rotation);
		float diff = ExtensionFunctions::ConvertTo180(desiredAngle - currentRotation);
		float desiredAngularVelocity;
		float desiredAngularAcceleration;

		if (fabs(diff) <= character->GetParams().angular_arrive_radius)
		{
			// Approaching target angle
			float lerpValue = fabs(diff) / character->GetParams().angular_arrive_radius;
			desiredAngularVelocity = FMath::Lerp(character->GetParams().max_angular_velocity, 0.0f, lerpValue) * ExtensionFunctions::Sign(diff);

			if (lerpValue > 0.99f)
			{
				lerpValue = 1;
			}

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("desiredAngularVelocity: %f"), desiredAngularVelocity));
			}

			desiredAngularAcceleration = desiredAngularVelocity - character->angularVelocity;
			result.angularAcceleration = desiredAngularAcceleration;
		}
		else
		{
			// Away from target angle
			desiredAngularAcceleration = character->GetParams().max_angular_acceleration * ExtensionFunctions::Sign(diff);
			result.angularAcceleration = desiredAngularAcceleration;
		}
	}



	return result;
}

AlignSteering::AlignSteering()
{
}

AlignSteering::~AlignSteering()
{
}
