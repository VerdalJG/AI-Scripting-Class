#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <CoreMinimal.h>

struct Params
{
    float max_velocity;
    float max_acceleration;
    float dest_radius;
    FVector targetPosition;
    float max_angular_velocity;
    float max_angular_acceleration;
    float angular_arrive_radius;
    float targetRotation;
    float look_ahead;
    float time_ahead;
};

struct Path
{
    TArray<FVector> points;
    FVector nearestPointOnPath;
    FVector seekTarget;
};

bool ReadParams(const char* filename, Params& params);
bool ReadPath(const char* filename, Path& path);

#endif