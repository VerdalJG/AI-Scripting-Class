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
	ReadPath("path.xml", m_path);


	seek = SeekSteering::SeekSteering();
	arrive = ArriveSteering::ArriveSteering();
	align = AlignSteering::AlignSteering();
	alignToMovement = AlignToMovementSteering::AlignToMovementSteering();
	path = PathSteering::PathSteering();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveAI(DeltaTime);
	DrawDebug();
}

void AAICharacter::MoveAI(float DeltaTime)
{
	m_target.targetPosition = m_params.targetPosition;
	m_target.targetRotation = m_params.targetRotation;

	FVector position = GetActorLocation();

	switch (steeringMode)
	{
		case SteeringMode::Seek:
		{
			acceleration = seek.GetSteering(this, m_target).linearAcceleration;
			velocity += acceleration * DeltaTime;
			velocity.GetClampedToMaxSize(m_params.max_velocity);
			position += velocity * DeltaTime;
			break;
		}
		
		case SteeringMode::Arrive:
		{
			acceleration = arrive.GetSteering(this, m_target).linearAcceleration;
			velocity += acceleration * DeltaTime;
			velocity.GetClampedToMaxSize(m_params.max_velocity);
			position += velocity * DeltaTime;
			break;
		}
		

		case SteeringMode::Align:
		{
			angularAcceleration = align.GetSteering(this, m_target).angularAcceleration;
			angularAcceleration = FMath::Clamp(angularAcceleration, -m_params.max_angular_acceleration, m_params.max_angular_acceleration);
			angularVelocity += angularAcceleration * DeltaTime;
			angularVelocity = FMath::Clamp(angularVelocity, -m_params.max_angular_velocity, m_params.max_angular_velocity);
			rotation += angularVelocity * DeltaTime;
			break;
		}
		

		case SteeringMode::AlignToMovement:
		{
			SteeringValues values = alignToMovement.GetSteering(this, m_target);
			acceleration = values.linearAcceleration;
			velocity += acceleration * DeltaTime;
			velocity.GetClampedToMaxSize(m_params.max_velocity);
			position += velocity * DeltaTime;
	
			angularAcceleration = values.angularAcceleration;
			angularAcceleration = FMath::Clamp(angularAcceleration, -m_params.max_angular_acceleration, m_params.max_angular_acceleration);
			angularVelocity += angularAcceleration * DeltaTime;
			angularVelocity = FMath::Clamp(angularVelocity, -m_params.max_angular_velocity, m_params.max_angular_velocity);
			rotation += angularVelocity * DeltaTime;
			break;
		}
		

		case SteeringMode::Path:
		{
			SteeringValues values = path.GetSteering(this, m_target);
			m_path.nearestPointOnPath = values.nearestPointOnPath;
			m_path.seekTarget = values.seekTarget;
			acceleration = values.linearAcceleration;
			velocity += acceleration * DeltaTime;
			velocity.GetClampedToMaxSize(m_params.max_velocity);
			position += velocity * DeltaTime;

			break;
		}
		
	}

	FVector rotationVector = FVector(0, rotation, 0);
	FRotator rotator = FRotator::MakeFromEuler(rotationVector);

	SetActorLocation(position);
	SetActorRotation(rotator);
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

	FVector dir = (mousePosition - GetActorLocation()).GetSafeNormal();
	float angle = FMath::RadiansToDegrees(atan2(dir.Z, dir.X));
	m_params.targetRotation = angle;
}

void AAICharacter::DrawDebug()
{
	SetPath(this, TEXT("BP_Path"), TEXT("path"), m_path.points, 5.0f, PathMaterial);
	SetCircle(targetCircle, TEXT("targetPosition"), m_params.targetPosition, m_params.dest_radius);
	SetCircle(nearPointCircle, TEXT("NearTarget"), m_path.nearestPointOnPath, m_params.dest_radius);
	SetCircle(seekTargetCircle, TEXT("SeekTarget"), m_path.seekTarget, m_params.dest_radius);
	SetArrow(this, TEXT("linear_acceleration"), acceleration, acceleration.Length());
	SetArrow(this, TEXT("linear_velocity"), velocity, velocity.Length());

	FVector dir(cos(FMath::DegreesToRadians(m_params.targetRotation)), 0.0f, sin(FMath::DegreesToRadians(m_params.targetRotation)));
	SetArrow(this, TEXT("target_rotation"), dir, 80.0f);

	TArray<TArray<FVector>> Polygons = {
		{ FVector(0.f, 0.f, 0.f), FVector(100.f, 0.f, 0.f), FVector(100.f, 0.f, 100.0f), FVector(0.f, 0.f, 100.0f) },
		{ FVector(100.f, 0.f, 0.f), FVector(200.f, 0.f, 0.f), FVector(200.f, 0.f, 100.0f) }
	};
	SetPolygons(this, TEXT("BP_Navmesh"), TEXT("mesh"), Polygons, NavmeshMaterial);
}