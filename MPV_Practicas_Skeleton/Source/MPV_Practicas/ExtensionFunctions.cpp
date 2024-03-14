// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtensionFunctions.h"

FVector ExtensionFunctions::LerpVector(FVector A, FVector B, double t)
{
	FVector result;
	result.X = FMath::Lerp(A.X, B.X, t);
	result.Y = FMath::Lerp(A.Y, B.Y, t);
	result.Z = FMath::Lerp(A.Z, B.Z, t);
	return result;
}

float ExtensionFunctions::ConvertTo360Angle(float angle)
{
	if (angle < 0)
	{
		int n = static_cast<int>(fabs(angle) / 360);
		angle += 360 * (n + 1);
	}
	else if (angle > 0)
	{
		int n = static_cast<int>(angle / 360);
		angle -= (360 * n);
	}

	return angle;
}

ExtensionFunctions::ExtensionFunctions()
{
}

ExtensionFunctions::~ExtensionFunctions()
{
}
