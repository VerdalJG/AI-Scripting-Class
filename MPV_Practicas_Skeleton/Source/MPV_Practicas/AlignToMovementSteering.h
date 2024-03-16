// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"
#include "AlignSteering.h"

/**
 * 
 */
class MPV_PRACTICAS_API AlignToMovementSteering : public ISteering
{
public:
	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) override;
	AlignToMovementSteering();
	~AlignToMovementSteering();

private:
	AlignSteering align;
};
