// Fill out your copyright notice in the Description page of Project Settings.


#include "ArriveSteering.h"
#include "AICharacter.h"

SteeringValues ArriveSteering::GetSteering(AActor* actor, FVector targetPosition)
{
	SteeringValues result;
	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);
		FVector actorLocation = actor->GetActorLocation();
		FVector distance = (targetPosition - actorLocation) / 100;
		FVector desiredVelocity = targetPosition - actorLocation;

		if (distance.Length() < character->GetParams().dest_radius)
		{
			float lerpValue = 1 - (distance.Length() / character->GetParams().dest_radius);
			if (lerpValue > 0.99)
			{
				lerpValue = 1;
			}
			desiredVelocity = LerpVector(desiredVelocity.GetSafeNormal() * character->GetParams().max_velocity, FVector::Zero(), lerpValue);
			FVector desiredAcceleration = desiredVelocity - character->velocity;
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

FVector ArriveSteering::LerpVector(FVector A, FVector B, double t)
{
	FVector result;
	result.X = FMath::Lerp(A.X, B.X, t);
	result.Y = FMath::Lerp(A.Y, B.Y, t);
	result.Z = FMath::Lerp(A.Z, B.Z, t);
	return result;
}

ArriveSteering::ArriveSteering()
{
	/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "[Your String Here]");
			}*/
}

ArriveSteering::~ArriveSteering()
{
}


