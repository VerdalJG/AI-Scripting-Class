#include "ExtensionFunctions.h"

FVector LerpVector(FVector A, FVector B, double t)
{
	FVector result;
	result.X = FMath::Lerp(A.X, B.X, t);
	result.Y = FMath::Lerp(A.Y, B.Y, t);
	result.Z = FMath::Lerp(A.Z, B.Z, t);
	return result;
}

float ConvertTo360(float angle)
{
	if (angle < 0)
	{
		int n = static_cast<int>(fabs(angle) / 360);
		angle += 360 * (n + 1);
	}
	else if (angle > 0)
	{
		int n = static_cast<int>(angle / 360);
		angle -= 360 * n;
	}

	return angle;
}

float ConvertTo180(float angle)
{
	angle = ConvertTo360(angle);

	if (angle > 180)
	{
		angle -= 360;
	}
	return angle;
}

float Sign(float n)
{
	if (n == 0.0f)
	{
		return 0.0f;
	}
	else
	{
		return n > 0.0f ? 1.0f : -1.0f;
	}
}