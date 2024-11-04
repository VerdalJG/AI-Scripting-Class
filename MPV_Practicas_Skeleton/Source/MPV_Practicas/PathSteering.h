// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"
#include "SeekSteering.h"


struct PathValues
{
	FVector nearestPoint;
	float squaredDistance;
	int currentPoint;

	PathValues()
	{
		nearestPoint = FVector(0, 0, 0);
		squaredDistance = 0;
		currentPoint = 0;
	}
};
/**
 * 
 */
class MPV_PRACTICAS_API PathSteering : public ISteering
{
public:
	PathSteering();
	virtual ~PathSteering() override;

	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) override;
	PathValues GetNearestPointOnSegment(FVector actorPosition, TArray<FVector> points);
	PathValues PointSegmentDistance(FVector point, FVector v1, FVector v2);
	FVector GetFuturePoint(PathValues& pathValues, TArray<FVector>& points, float lookAhead);


private:
	SeekSteering seek;
};

/*
   Link: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
*/
