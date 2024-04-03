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
		FVector actorLocation = actor->GetActorLocation();
		PathValues nearestPointOnSegment = GetNearestPointOnSegment(actorLocation, target.path);

		float lookAhead = character->GetParams().look_ahead;

		while (lookAhead > 0)
		{
			// look ahead on segment to find point
		}

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
		p.currentPoint = i;
		if (i == points.Num() - 1) // Last point should compare with first
		{
			p = PointSegmentDistance(actorPosition, points[i], points[0]);
		}
		else
		{
			p = PointSegmentDistance(actorPosition, points[i], points[i + 1]);
		}

		if (i == 0) // If this is the first point we compare, just set minDistance and result
		{
			minDistance = p.squaredDistance;
			result = p;
		}
		else // Ensure that we get the lowest distance
		{
			if (p.squaredDistance < minDistance)
			{
				minDistance = p.squaredDistance;
				result = p;
			}
		}
	}
	return result;
}

PathValues PathSteering::PointSegmentDistance(FVector point, FVector p1, FVector p2)
{
	PathValues result;
	float A = point.X - p1.X;
	float B = point.Y - p1.Y;
	float C = p2.X - p1.X;
	float D = p2.Y - p1.Y;

	float dotProduct = A * C + B * D;
	float lengthSquared = C * C + D * D;
	float param = -1;

	if (lengthSquared != 0)
	{
		param = dotProduct / lengthSquared;
	}
	
	if (param < 0) // Closest point in the segment is p1
	{
		result.nearestX = p1.X;
		result.nearestY = p1.Y;
	}
	else if (param > 1)
	{
		result.nearestX = p2.X;
		result.nearestY = p2.Y;
	}
	else // Dot product is 0, means that there is a perpendicular line that intersects segment. We add the projection to get how far along the line we need to go
	{
		result.nearestX = p1.X + param * C;
		result.nearestY = p1.Y + param * D;
	}
	float dx = point.X - result.nearestX;
	float dy = point.Y - result.nearestY;

	result.squaredDistance = dx * dx + dy * dy; // Don't need to square root, as this will only be used for comparison, small optimization.

	return result;
}

PathSteering::PathSteering()
{
}

PathSteering::~PathSteering()
{
}
