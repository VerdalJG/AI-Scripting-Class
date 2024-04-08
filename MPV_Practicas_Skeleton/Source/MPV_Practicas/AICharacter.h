// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "params/params.h"
#include "GameFramework/PlayerController.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "AlignSteering.h"
#include "AlignToMovementSteering.h"
#include "PathSteering.h"

#include "AICharacter.generated.h"

#define print(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT(x));}

#define printf(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}

UENUM(BlueprintType)
enum class SteeringMode
{
	Seek,
	Arrive,
	Align,
	AlignToMovement,
	Path
};

UCLASS()
class MPV_PRACTICAS_API AAICharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAICharacter();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIChar)
	uint32 bDoMovement : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
	AActor* targetCircle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
	AActor* nearPointCircle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
	AActor* seekTargetCircle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
		UMaterialInterface* PathMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
		UMaterialInterface* NavmeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
		UMaterialInterface* SeekMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIChar)
		SteeringMode steeringMode;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	Params m_params;

	Path m_path;

	TargetValues m_target;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveAI(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AIFunctions")
	void OnClickedLeft(const FVector& mousePosition);
	UFUNCTION(BlueprintCallable, Category = "AIFunctions")
	void OnClickedRight(const FVector& mousePosition);
	
	const Params& GetParams() const { return m_params; }
	const Path& GetPath() const { return m_path; }

	void DrawDebug();

	FVector velocity;
	FVector acceleration;
	float rotation;
	float angularVelocity;
	float angularAcceleration;

	




private:

	SeekSteering seek;
	ArriveSteering arrive;
	AlignSteering align;
	AlignToMovementSteering alignToMovement;
	PathSteering path;
};
