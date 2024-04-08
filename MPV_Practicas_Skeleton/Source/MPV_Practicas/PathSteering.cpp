// Fill out your copyright notice in the Description page of Project Settings.


#include "PathSteering.h"
#include "AICharacter.h"
#include "ExtensionFunctions.h"

SteeringValues PathSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;
	seek = SeekSteering::SeekSteering();

	if (Cast<AAICharacter>(actor))
	{
		AAICharacter* character = Cast<AAICharacter>(actor);
		FVector actorLocation = actor->GetActorLocation();
		Path path = character->GetPath();
		PathValues nearestPointOnSegment = GetNearestPointOnSegment(actorLocation, path.points);
		result.nearestPointOnPath = nearestPointOnSegment.nearestPoint;

		float lookAhead = character->GetParams().look_ahead;
		target.targetPosition = GetFuturePoint(nearestPointOnSegment, path.points, lookAhead);
		result.seekTarget = target.targetPosition;
		result.linearAcceleration = seek.GetSteering(actor, target).linearAcceleration;

	}

	return result;
}

PathValues PathSteering::GetNearestPointOnSegment(FVector actorPosition, TArray<FVector> points)
{
	PathValues result;
	float minDistance = 0;
	for (int i = 0; i < points.Num(); i++)
	{
		PathValues p;
		int nextPoint = (i + 1) % points.Num();
		p = PointSegmentDistance(actorPosition, points[i], points[nextPoint]);
		p.currentPoint = i;
		

		if (i == 0) // If this is the first point we compare, just set minDistance and result
		{
			minDistance = p.squaredDistance;
			result = p;
		}
		else // Ensure that we get the lowest distance
		{
			if (p.squaredDistance <= minDistance)
			{
				minDistance = p.squaredDistance;
				result = p;
			}
		}
	}
	return result;
}


// This is specifically for FINITE line segments. This code would be much simpler for infinite line segments
PathValues PathSteering::PointSegmentDistance(FVector point, FVector p1, FVector p2)
{
	PathValues result;
	float A = point.X - p1.X;
	float B = point.Z - p1.Z;
	float C = p2.X - p1.X;
	float D = p2.Z - p1.Z;

	float dotProduct = A * C + B * D;
	float lengthSquared = C * C + D * D;
	float param = -1;

	if (lengthSquared != 0)
	{
		param = dotProduct / lengthSquared;
	}
	
	if (param < 0) // Closest point in the segment is p1
	{
		result.nearestPoint.X = p1.X;
		result.nearestPoint.Z = p1.Z;
	}
	else if (param > 1) // Closest point in the segment is p2
	{
		result.nearestPoint.X = p2.X;
		result.nearestPoint.Z = p2.Z;
	}
	else // Closest point is within segment. We add the projection with point #1 to get how far along the line we need to go.
	{
		result.nearestPoint.X = p1.X + param * C;
		result.nearestPoint.Z = p1.Z + param * D;
	}
	float dx = point.X - result.nearestPoint.X;
	float dy = point.Z - result.nearestPoint.Z;

	result.squaredDistance = dx * dx + dy * dy; // Don't need to square root, as this will only be used for comparison, small optimization.

	return result;
}

FVector PathSteering::GetFuturePoint(PathValues& pathValues, TArray<FVector>& points, float lookAhead)
{
	FVector result = pathValues.nearestPoint;
	int currentPoint = pathValues.currentPoint;
	

	while (lookAhead > 0)
	{
		int nextPoint = (currentPoint + 1) % points.Num();
		FVector dir = points[nextPoint] - points[currentPoint];
		float distance = FVector::Dist(result, points[nextPoint]);
		if (distance > lookAhead)
		{
			result += dir.GetSafeNormal() * lookAhead;
			lookAhead = 0;
		}
		else
		{
			result += dir.GetSafeNormal() * distance;
			lookAhead -= distance;
			currentPoint = nextPoint;
		}
		
	}
	return result;
}

PathSteering::PathSteering()
{
}

PathSteering::~PathSteering()
{
}
