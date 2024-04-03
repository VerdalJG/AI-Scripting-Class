// Fill out your copyright notice in the Description page of Project Settings.


#include "PathSteering.h"
#include "AICharacter.h"
#include "ExtensionFunctions.h"

SteeringValues PathSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;

	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);

	}

	return result;
}

PathSteering::PathSteering()
{
}

PathSteering::~PathSteering()
{
}
