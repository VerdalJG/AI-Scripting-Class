// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "params/params.h"

struct SteeringValues
{
	FVector linearAcceleration = FVector::Zero();
	float angularAcceleration = 0.0f;
};

struct TargetValues
{
	FVector targetPosition = FVector::Zero();
	float targetRotation = 0.0f;
	TArray<FVector> path;
};

class MPV_PRACTICAS_API ISteering
{
public:
	virtual ~ISteering();
	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) = 0;
};




