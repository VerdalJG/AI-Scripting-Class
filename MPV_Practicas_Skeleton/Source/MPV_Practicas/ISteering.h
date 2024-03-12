// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "params/params.h"

struct SteeringValues
{
	FVector linearAcceleration = FVector::Zero();
	FVector angularAcceleration = FVector::Zero();
};

class MPV_PRACTICAS_API ISteering
{
public:
	virtual ~ISteering();

	virtual SteeringValues GetSteering(AActor* actor, FVector targetPosition) = 0;
};




