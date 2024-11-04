// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinder.h"
#include "AICharacter.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::Pathfinder(AAICharacter* player)
{
	this->player = player;
}

Pathfinder::~Pathfinder()
{
	ClearLists();
}

FVector Pathfinder::SetPositionInGrid(float X, float Z)
{
	FVector result = FVector::Zero();
	Grid grid = player->GetGrid();

	for (int i = 0; i < grid.rows; i++)
	{
		for (int j = 0; j < grid.columns; j++)
		{
			FVector cellPosition = grid.cells[i][j].position;

			float cellMinX = cellPosition.X - CELL_SIZE / 2;
			float cellMinZ = cellPosition.Z - CELL_SIZE / 2;
			float cellMaxX = cellPosition.X + CELL_SIZE / 2;
			float cellMaxZ = cellPosition.Z + CELL_SIZE / 2;

			// Check if X and Z coordinates are within the bounds of the cell
			if (X <= cellMaxX && X >= cellMinX && Z <= cellMaxZ && Z >= cellMinZ)
			{
				result = cellPosition;
				return result;
			}
		}
	}
	return result;
}

void Pathfinder::UpdatePath()
{
	// Reset final path array
	finalPath.Empty();

	// Initialize starting node
	Node* startingPathNode = new Node();
	startingPathNode->position = startPosition;
	startingPathNode->g = 0.0f; // Cost from start to current node - initial cost is 0
	startingPathNode->h = CalculateHeuristic(startPosition);
	startingPathNode->f = startingPathNode->g + startingPathNode->h; // Total cost

	// Add starting node to the open list
	openList.Add(startingPathNode);

	// A* loop - continues until open list is empty
	while (!openList.IsEmpty())
	{
		// Get the node with the lowest total cost (f) from the open list
		Node* currentNode = ShortestNode(openList);
		openList.Remove(currentNode);

		// Check if we are at the goal
		if (IsGoal(currentNode->position))
		{
			// Backtrack to construct the final path
			finalPath.Add(currentNode->position);
			while (currentNode->parent != nullptr)
			{
				currentNode = currentNode->parent;
				finalPath.Add(currentNode->position);
			}
			break;
		}

		closedList.Add(currentNode); // Move current node to closed list
		TArray<Node*> neighbors = GetNeighbors(currentNode);

		// Iterate through each neighbor
		for (Node* neighbor : neighbors)
		{
			// Skip if a node with the same position is already in the closed list
			if (GetNodeByPosition(closedList, neighbor->position))
			{
				delete neighbor;
				continue;
			}

			// Calculate heuristic for this neighbor and total cost consequently
			neighbor->h = CalculateHeuristic(neighbor->position);
			neighbor->f = neighbor->g + neighbor->h;

			// Check if neighbor is already in the open list
			Node* openNeighbor = GetNodeByPosition(openList, neighbor->position);
			if (openNeighbor == nullptr) // Not in open list
			{
				openList.Add(neighbor); // Add new neighbor to open list
			}
			else
			{
				// If it's in the open list, check if the new path is better
				if (neighbor->g < openNeighbor->g)
				{
					// Update the existing node with the better path
					openNeighbor->g = neighbor->g;
					openNeighbor->f = openNeighbor->g + openNeighbor->h;
					openNeighbor->parent = currentNode;

					delete neighbor; // Clean up memory for redundant neighbor
				}
				else
				{
					delete neighbor; // Discard if current path isn't better
				}
			}
		}
	}

	ClearLists();
}
Node* Pathfinder::GetNodeByPosition(TArray<Node*>& list, FVector position)
{
	for (Node* node : list)
	{
		if (node->position == position)
		{
			return node; // Return existing node if position matches
		}
	}
	return nullptr; // No match found
}

void Pathfinder::ClearLists()
{
	// Free memory
	for (Node* node : openList)
	{
		delete node;
	}
	openList.Empty();

	for (Node* node : closedList)
	{
		delete node;
	}
	closedList.Empty();
}

void Pathfinder::SetStartPosition(float X, float Z)
{
	startPosition = SetPositionInGrid(X, Z);
}

void Pathfinder::SetEndPosition(float X, float Z)
{
	endPosition = SetPositionInGrid(X, Z);
	UpdatePath();
}

// Finds and returns the node in the list with the lowest f-cost
Node* Pathfinder::ShortestNode(TArray<Node*> list)
{
	Node* shortestNode = list[0];
	for (Node* node : list)
	{
		if (node->f < shortestNode->f)
		{
			shortestNode = node; // Update lowest cost node
		}
	}
	return shortestNode;
}

// Checks if a given node's position matches the goal (end position)
bool Pathfinder::IsGoal(FVector nodePosition)
{
	return nodePosition == endPosition;
}

bool Pathfinder::IsWithinBounds(FVector nodePosition)
{
	float x = nodePosition.X;
	float Z = nodePosition.Z;

	float minX = -horizontalBounds;
	float minZ = -verticalBounds;
	float maxX = horizontalBounds;
	float maxZ = verticalBounds;

	return (x >= minX && x <= maxX && Z >= minZ && Z <= maxZ);
}

// Calculates heuristic distance (diagonal shortcut) between two points
float Pathfinder::CalculateHeuristic(FVector currentNode)
{
	return FVector::Dist(currentNode, endPosition);
}

// Gets neighbors of a node, considering the cost of moving to each neighbor
TArray<Node*> Pathfinder::GetNeighbors(Node* currentNode)
{
	TArray<Node*> neighbors;
	Grid grid = player->GetGrid();

	for (const auto& directionPair : directionOffsets)
	{
		FVector neighborPosition = currentNode->position + directionPair.Value;

		if (!IsWithinBounds(neighborPosition))
		{
			continue; // Skip out of bounds cells
		}

		int i = static_cast<int>(((neighborPosition.X + horizontalBounds) - CELL_SIZE / 2) / CELL_SIZE);
		int j = static_cast<int>(((neighborPosition.Z + verticalBounds) - CELL_SIZE / 2) / CELL_SIZE);

		if (grid.cells[j][i].cost < 100) // Only consider passable cells
		{
			Node* neighbor = new Node();
			neighbor->position = neighborPosition;
			neighbor->parent = currentNode;
			neighbor->g = currentNode->g + grid.cells[j][i].cost;
			neighbor->h = CalculateHeuristic(neighborPosition);
			neighbor->f = neighbor->g + neighbor->h;

			neighbors.Add(neighbor);
			//// Avoid duplicate additions to the open list or better paths
			//if (!closedList.Contains(neighbor) && (!openList.Contains(neighbor) || neighbor->g < openList[openList.Find(neighbor)]->g))
			//{
			//	neighbors.Add(neighbor);
			//}
			//else
			//{
			//	delete neighbor;
			//}
		}
	}

	return neighbors;
}


