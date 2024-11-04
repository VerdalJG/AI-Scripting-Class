// Fill out your copyright notice in the Description page of Project Settings.


#include "PathObstacleAvoidanceSteering.h"
#include "PathSteering.h"
#include "AICharacter.h"

PathObstacleAvoidanceSteering::PathObstacleAvoidanceSteering()
{
}

PathObstacleAvoidanceSteering::~PathObstacleAvoidanceSteering()
{
}

SteeringValues PathObstacleAvoidanceSteering::GetSteering(AActor* actor, TargetValues target)
{
	SteeringValues result;
	pathSteering = PathSteering::PathSteering();
	
	if (AAICharacter* character = Cast<AAICharacter>(actor))
	{
		Params params = character->GetParams();
		FVector normalizedVelocity = character->velocity.GetSafeNormal();
		FVector actorPosition = character->GetActorLocation();
		TArray<Obstacle> obstacles = character->GetObstacles();

		FVector avoidanceVector = FVector(0, 0, 0);

		for (Obstacle& obstacle : obstacles)
		{
			FVector obstaclePosition = obstacle.position;
			FVector actorToObstacle = obstaclePosition - actorPosition;
			float projection = FVector::DotProduct(actorToObstacle, normalizedVelocity);

			if (projection < 0) // Skip if obstacle is behind the character
			{
				obstacle.color = FLinearColor(0.0f, 255.0f, 0.0f, 0.5f); // Green
				continue;
			}

			FVector closestPoint = actorPosition + normalizedVelocity * projection;
			float distanceToObstacle = FVector::Distance(closestPoint, obstaclePosition);

			if (distanceToObstacle < obstacle.radius + params.char_radius)
			{
				// Obstacle is close enough
				obstacle.color = FLinearColor(255.0f, 0.0f, 0.0f, 0.5f); // Red

				// Calculate a force to steer around the obstacle
				FVector avoidanceDirection = closestPoint - obstaclePosition;
				avoidanceDirection.Normalize();
				avoidanceVector += avoidanceDirection * params.max_acceleration;
			}
			else
			{
				// No avoidance needed, obstacle is far enough
				obstacle.color = FLinearColor(255.0f, 255.0f, 255.0f, 0.5f); // White
			}
		}
		if (!avoidanceVector.IsNearlyZero()) // To avoid floating point imprecisions
		{
			result.linearAcceleration = avoidanceVector;
		}
		else
		{
			// If no obstacles in the path, follow normal path steering
			result = pathSteering.GetSteering(actor, target);
		}
	}
	return result;
}
