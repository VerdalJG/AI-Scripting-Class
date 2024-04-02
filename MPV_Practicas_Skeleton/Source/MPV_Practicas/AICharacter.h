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

#include "AICharacter.generated.h"

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
	AActor* circle;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* PathMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* NavmeshMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	Params m_params;
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

	void DrawDebug();

	FVector velocity;
	FVector acceleration;
	float rotation;
	float angularVelocity;
	float angularAcceleration;

	enum class SteeringMode
	{
		Seek,
		Arrive,
		Align,
		AlignToMovement
	};


private:
	SteeringMode steeringMode;
	SeekSteering seek;
	ArriveSteering arrive;
	AlignSteering align;
	AlignToMovementSteering alignToMovement;
};
