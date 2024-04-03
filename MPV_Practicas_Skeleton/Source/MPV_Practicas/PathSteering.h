// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"

/**
 * 
 */
class MPV_PRACTICAS_API PathSteering : public ISteering
{
public:
	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) override;
	PathSteering();
	virtual ~PathSteering() override;
};

/*
   Link: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
*/
