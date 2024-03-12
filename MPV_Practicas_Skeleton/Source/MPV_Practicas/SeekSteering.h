// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"

/**
 * 
 */
class MPV_PRACTICAS_API SeekSteering : public ISteering
{
public:
	virtual SteeringValues GetSteering(AActor* actor, FVector targetPosition) override;

	SeekSteering();
	virtual ~SeekSteering() override;
};
