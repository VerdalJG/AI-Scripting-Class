// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "params/params.h"
#include "debug/debugdraw.h"



// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	ReadParams("params.xml", m_params);
	
	steeringMode = SteeringMode::Align;

	switch (steeringMode)
	{
	case SteeringMode::Seek:
		seek = SeekSteering::SeekSteering();
		break;
	case SteeringMode::Arrive:
		arrive = ArriveSteering::ArriveSteering();
		break;
	case SteeringMode::Align:
		align = AlignSteering::AlignSteering();
		break;
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebug();

	MoveAI(DeltaTime);
}

void AAICharacter::MoveAI(float DeltaTime)
{
	m_target.targetPosition = m_params.targetPosition;
	m_target.targetRotation = m_params.targetRotation;

	FVector position = GetActorLocation();
	float rotation = GetActorRotation().Pitch;
	
	switch (steeringMode)
	{
	case SteeringMode::Seek:
		acceleration = seek.GetSteering(this, m_target).linearAcceleration;
		velocity += acceleration * DeltaTime;
		position += velocity * DeltaTime;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "seek");
		}
		break;
	case SteeringMode::Arrive:
		acceleration = arrive.GetSteering(this, m_target).linearAcceleration;
		velocity += acceleration * DeltaTime;
		position += velocity * DeltaTime;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "arrive");
		}
		break;
	case SteeringMode::Align:
		angularAcceleration = align.GetSteering(this, m_target).angularAcceleration;
		angularVelocity += angularAcceleration * DeltaTime;
		rotation += angularVelocity * DeltaTime;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "align");
		}
		break;
	}

	SetActorLocation(position);
	SetActorRotation(FRotator(rotation, 0, 0));
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnClickedLeft(const FVector& mousePosition)
{
	SetActorLocation(mousePosition);
}

void AAICharacter::OnClickedRight(const FVector& mousePosition)
{
	m_params.targetPosition = mousePosition;
}

void AAICharacter::DrawDebug()
{
	SetCircle(circle, TEXT("targetPosition"), m_params.targetPosition, m_params.dest_radius * 100);
	SetArrow(this, TEXT("linear_acceleration"), acceleration, acceleration.Length());
	SetArrow(this, TEXT("linear_velocity"), velocity, velocity.Length());
}