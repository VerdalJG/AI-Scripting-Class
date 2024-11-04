#include "params.h"

#include "XmlFile.h"
#include "Misc/DefaultValueHelper.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

bool ReadParams(const char* filename, Params& params)
{
	FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

	// Log or use the current working directory
	UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

	FString ContentFolderDir = FPaths::ProjectContentDir();

	//FString FilePath(TEXT("./params.xml"));
	FString params_path = filename;
	FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
	UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);

	
	FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);
	
	if (MyXml.GetRootNode())
	{
		const FXmlNode* RootNode = MyXml.GetRootNode();
	
		const FString MyChildTag("params");
		const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

		const FXmlNode* paramElem = MyChildNode->FindChildNode(TEXT("max_velocity"));
		FString value;
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.max_velocity);

		}

		paramElem = MyChildNode->FindChildNode(TEXT("max_acceleration"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.max_acceleration);

		}

		paramElem = MyChildNode->FindChildNode(TEXT("dest_radius"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.dest_radius);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("targetPosition"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("x");
			float x;
			FDefaultValueHelper::ParseFloat(value, x);
			params.targetPosition.X = x;
			value = paramElem->GetAttribute("z");
			float z;
			FDefaultValueHelper::ParseFloat(value, z);
			params.targetPosition.Z = z;
			params.targetPosition.Y = 0.0f;
		}

		paramElem = MyChildNode->FindChildNode(TEXT("max_angular_velocity"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.max_angular_velocity);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("max_angular_acceleration"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.max_angular_acceleration);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("angular_arrive_radius"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.angular_arrive_radius);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("targetRotation"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.targetRotation);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("look_ahead"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.look_ahead);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("time_ahead"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.time_ahead);
		}

		paramElem = MyChildNode->FindChildNode(TEXT("char_radius"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.char_radius);
		}
	}
	return true;
}

bool ReadPath(const char* filename, Path& path)
{
	FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

	// Log or use the current working directory
	UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

	FString ContentFolderDir = FPaths::ProjectContentDir();

	//FString FilePath(TEXT("./params.xml"));
	FString params_path = filename;
	FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
	UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);


	FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);

	if (MyXml.GetRootNode())
	{
		const FXmlNode* RootNode = MyXml.GetRootNode();

		const FString MyChildTag("points");
		const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

		FString value;

		for (FXmlNode* point : MyChildNode->GetChildrenNodes())
		{
			value = point->GetAttribute("x");
			float x;
			FDefaultValueHelper::ParseFloat(value, x);
			value = point->GetAttribute("y");
			float z;
			FDefaultValueHelper::ParseFloat(value, z);
			path.points.Add(FVector(x, 0, z));
		}
	}
	return true;
}

bool ReadGrid(const char* filename, Grid& grid)
{
	FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

	// Log or use the current working directory
	UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

	FString ContentFolderDir = FPaths::ProjectContentDir();

	FString gridFileName = filename;
	FString FilePath = FPaths::Combine(*ContentFolderDir, *gridFileName);
	UE_LOG(LogTemp, Log, TEXT("Grid Params Path: %s"), *FilePath);

	FString RetString = "";

	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Could not open file : %s"), *FilePath);
	}
	for (int i = 0; i < RetString.Len(); i++)
	{
		if (RetString[i] == '\r' || RetString[i] == '\n')
		{
			RetString.RemoveAt(i);
			--i;
		}
	}
	for (int i = 0; i < GRID_ROWS; i++)
	{
		TArray<Cell> row;
		for (int j = 0; j < GRID_COLUMNS; j++)
		{
			Cell cell;
			float horizontalBoundary = (GRID_COLUMNS * CELL_SIZE) / 2; // 950
			float verticalBoundary = (GRID_ROWS * CELL_SIZE) / 2; // 500
			float xPosition = j * CELL_SIZE + (CELL_SIZE / 2) - horizontalBoundary;
			float zPosition = i * CELL_SIZE + (CELL_SIZE / 2) - verticalBoundary;

			cell.position = FVector(xPosition, 0, zPosition);
			char character = RetString[GRID_COLUMNS * i + j];
			if (character == '.')
			{
				cell.cost = 1;
			}
			if (character == '#')
			{
				cell.cost = 100;
			}
			row.Add(cell);
		}
		grid.cells.Add(row);
	}
	return true;
}

bool ReadObstacles(const char* filename, TArray<Obstacle>& obstacles)
{
	FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

	// Log or use the current working directory
	UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

	FString ContentFolderDir = FPaths::ProjectContentDir();

	FString params_path = filename;
	FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
	UE_LOG(LogTemp, Log, TEXT("Obstacles Params Path: %s"), *FilePath);


	FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);

	if (MyXml.GetRootNode())
	{
		const FXmlNode* RootNode = MyXml.GetRootNode();

		const FString MyChildTag("obstacles");
		const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

		FString value;
		for (FXmlNode* point : MyChildNode->GetChildrenNodes())
		{
			value = point->GetAttribute("x");
			float x;
			FDefaultValueHelper::ParseFloat(value, x);
			value = point->GetAttribute("y");
			float z;
			FDefaultValueHelper::ParseFloat(value, z);
			value = point->GetAttribute("r");
			float radius;
			FDefaultValueHelper::ParseFloat(value, radius);
			Obstacle newObstacle;
			newObstacle.position = FVector(x, 0.0f, z);
			newObstacle.radius = radius;
			obstacles.Add(newObstacle);
		}

	}
	return true;
}
