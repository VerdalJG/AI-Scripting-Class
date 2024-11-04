#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <CoreMinimal.h>

#define GRID_ROWS 20
#define GRID_COLUMNS 38 // This number matches with the boundaries of the viewport - 950 on each side
#define CELL_SIZE 50

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
    float char_radius;
};

struct Obstacle
{
    FVector position;
    float radius;
    FLinearColor color;
};

struct Path
{
    TArray<FVector> points;
    FVector nearestPointOnPath;
    FVector seekTarget;
};

struct Cell 
{
    FVector position;
    int cost = 0;
};

struct Grid
{
    TArray<TArray<Cell>> cells;
    int rows = GRID_ROWS;
    int columns = GRID_COLUMNS;
};

bool ReadParams(const char* filename, Params& params);
bool ReadPath(const char* filename, Path& path);
bool ReadObstacles(const char* filename, TArray<Obstacle>& obstacles);
bool ReadGrid(const char* filename, Grid& grid);

#endif