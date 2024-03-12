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

	velocity = FVector(-100, 0, 100);
	arrive = ArriveSteering::ArriveSteering();
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
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "[Your String Here]");
	}*/


	FVector position = GetActorLocation();

	acceleration = arrive.GetSteering(this, m_params.targetPosition).linearAcceleration;
	velocity += acceleration * DeltaTime;
	position += velocity * DeltaTime;

	SetActorLocation(position);
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