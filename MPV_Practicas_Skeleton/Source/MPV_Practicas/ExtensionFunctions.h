// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
static class MPV_PRACTICAS_API ExtensionFunctions
{
public:
	static FVector LerpVector(FVector A, FVector B, double t);
	static float ConvertTo360Angle(float angle);
	ExtensionFunctions();
	~ExtensionFunctions();
};
