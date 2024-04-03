// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"
#include "SeekSteering.h"


struct PathValues
{
	float nearestX, nearestY;
	float squaredDistance;
	int currentPoint;
};
/**
 * 
 */
class MPV_PRACTICAS_API PathSteering : public ISteering
{
public:
	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) override;
	PathValues GetNearestPointOnSegment(FVector actorPosition, TArray<FVector> points);
	PathValues PointSegmentDistance(FVector point, FVector v1, FVector v2);
	PathSteering();
	virtual ~PathSteering() override;

private:
	SeekSteering seek;
};

/*
   Link: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
*/
