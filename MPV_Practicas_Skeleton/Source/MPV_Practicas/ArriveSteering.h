// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"


class MPV_PRACTICAS_API ArriveSteering : public ISteering
{


public:
	virtual SteeringValues GetSteering(AActor* actor, FVector targetPosition) override;

	FVector LerpVector(FVector A, FVector B, double t);
	ArriveSteering();
	virtual ~ArriveSteering() override;
};
