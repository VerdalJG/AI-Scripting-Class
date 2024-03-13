// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"


class MPV_PRACTICAS_API ArriveSteering : public ISteering
{
public:
	virtual SteeringValues GetSteering(AActor* actor, TargetValues target) override;
	ArriveSteering();
	virtual ~ArriveSteering() override;
};
