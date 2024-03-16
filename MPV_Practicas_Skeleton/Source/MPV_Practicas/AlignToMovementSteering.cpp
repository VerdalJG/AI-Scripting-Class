// Fill out your copyright notice in the Description page of Project Settings.


#include "AlignToMovementSteering.h"
#include "AICharacter.h"
#include "ExtensionFunctions.h"



SteeringValues AlignToMovementSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;
	align = AlignSteering::AlignSteering();

	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);

		FVector dir = (character->velocity.GetSafeNormal());
		float angle = FMath::RadiansToDegrees(atan2(dir.Z, dir.X));
		target.targetRotation = angle;
		float angularAcceleration = align.GetSteering(actor, target).angularAcceleration;
		result.angularAcceleration = angularAcceleration;
	}

	return result;
}

AlignToMovementSteering::AlignToMovementSteering()
{
}

AlignToMovementSteering::~AlignToMovementSteering()
{
}
