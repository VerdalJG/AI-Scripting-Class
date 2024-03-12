// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekSteering.h"
#include "AICharacter.h"

SteeringValues SeekSteering::GetSteering(AActor* actor, FVector targetPosition)
{
	SteeringValues result;
	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);
		FVector actorLocation = actor->GetActorLocation();
		FVector desiredVelocity = targetPosition - actorLocation;
		desiredVelocity = desiredVelocity.GetSafeNormal() * character->GetParams().max_velocity;
		
		FVector desiredAcceleration = desiredVelocity - character->velocity;
		desiredAcceleration = desiredAcceleration.GetSafeNormal() * character->GetParams().max_acceleration;
		result.linearAcceleration = desiredAcceleration;
	}
	return result;
}

SeekSteering::SeekSteering()
{
}

SeekSteering::~SeekSteering()
{
}
