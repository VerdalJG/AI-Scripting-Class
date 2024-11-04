// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathSteering.h"

/**
 * 
 */
class MPV_PRACTICAS_API PathObstacleAvoidanceSteering : public ISteering
{

public:
	PathObstacleAvoidanceSteering();
	virtual ~PathObstacleAvoidanceSteering() override;

	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) override;

private:
	PathSteering pathSteering;
};
