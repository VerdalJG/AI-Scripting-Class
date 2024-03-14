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

	seek = SeekSteering::SeekSteering();
	arrive = ArriveSteering::ArriveSteering();
	align = AlignSteering::AlignSteering();
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


	switch (steeringMode)
	{
	case SteeringMode::Seek:
		acceleration = seek.GetSteering(this, m_target).linearAcceleration;
		velocity += acceleration * DeltaTime;
		position += velocity * DeltaTime;
		break;
	case SteeringMode::Arrive:
		acceleration = arrive.GetSteering(this, m_target).linearAcceleration;
		velocity += acceleration * DeltaTime;
		position += velocity * DeltaTime;
		break;
	case SteeringMode::Align:
		angularAcceleration = align.GetSteering(this, m_target).angularAcceleration;
		angularVelocity += angularAcceleration * DeltaTime;
		rotation += angularVelocity * DeltaTime;
		break;
	}
	FVector rotationVector = FVector(0, rotation, 0);
	FRotator rotationRotator = FRotator::MakeFromEuler(rotationVector);

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Rotation: %f"), rotation));
	}*/

	SetActorLocation(position);
	SetActorRotation(rotationRotator);
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