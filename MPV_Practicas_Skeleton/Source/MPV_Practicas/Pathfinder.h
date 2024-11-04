// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "params/params.h"

struct Node
{
	Node* parent = nullptr; // For path reconstruction
	FVector position;
	float f; // Total cost
	float g; // Cost to reach this node
	float h; // Heuristic


	// Constructor for convenience
	/*Node(FVector inPoint, float inG = 0.0f, float inH = 0.0f) : 
		position(inPoint),
		g(inG),
		h(inH)
	{
		f = g + h;
	}*/

	// Less-than operator for sorting (lowest f-score prioritized)
	bool operator<(const Node& other) const
	{
		return f > other.f; // Priority queue is max heap by default, so we invert the expression
	}
};

enum class EDirection : uint8
{
	Up,    
	Down,       
	Left,       
	Right,      
	UpLeft,    
	UpRight,    
	DownLeft,   
	DownRight  
};

class AAICharacter;

/**
 * 
 */
class MPV_PRACTICAS_API Pathfinder
{
public:
	Pathfinder();
	Pathfinder(AAICharacter* player);
	~Pathfinder();

	FVector SetPositionInGrid(float X, float Z);

	Node* ShortestNode(TArray<Node*> list);
	bool IsGoal(FVector nodePosition);
	bool IsWithinBounds(FVector nodePosition);

	float CalculateHeuristic(FVector currentNode);
	TArray<Node*> GetNeighbors(Node* currentNode);
	void UpdatePath();
	Node* GetNodeByPosition(TArray<Node*>& list, FVector position);
	void ClearLists();

	// Direction offsets map for 8-way movement in the grid
	TMap<EDirection, FVector> directionOffsets = 
	{
		{EDirection::Up, FVector(0, 0, CELL_SIZE)},
		{EDirection::Down, FVector(0, 0, -CELL_SIZE)},
		{EDirection::Left, FVector(-CELL_SIZE, 0, 0)},
		{EDirection::Right, FVector(CELL_SIZE, 0, 0)},
		{EDirection::UpLeft, FVector(-CELL_SIZE, 0, CELL_SIZE)},
		{EDirection::UpRight, FVector(CELL_SIZE, 0, CELL_SIZE)},
		{EDirection::DownLeft, FVector(-CELL_SIZE, 0, -CELL_SIZE)},
		{EDirection::DownRight, FVector(CELL_SIZE, 0, -CELL_SIZE)}
	};

private:
	// Start and end points for the path
	FVector startPosition = FVector::ZeroVector;
	FVector endPosition = FVector::ZeroVector;

	float horizontalBounds = (GRID_COLUMNS * CELL_SIZE) / 2;
	float verticalBounds = (GRID_ROWS * CELL_SIZE) / 2;

	TArray<FVector> finalPath;
	TArray<Node*> openList; // Nodes available for exploration
	TArray<Node*> closedList; // Nodes already processed

	AAICharacter* player = nullptr;

public:
	// Getters for start and end points
	FVector GetStartPosition() const { return startPosition; }
	FVector GetEndPosition() const { return endPosition; }

	// Setters for start and end points
	void SetStartPosition(float X, float Z);
	void SetEndPosition(float X, float Z);

	TArray<FVector> GetFinalPath() const { return finalPath; }
};
