// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleMovingPlatform.h"


// Sets default values
ASimpleMovingPlatform::ASimpleMovingPlatform()
	:PlatformVelocity(FVector(100, 0, 0)), MoveDistance(100.f), RotationVelocity(FRotator::ZeroRotator)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);
}

// Called every frame
void ASimpleMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsWaiting){
		MovePlatform(DeltaTime);
		RotatePlatform(DeltaTime);
	} else {
		TimeSinceLastReverse += DeltaTime;
		if (TimeSinceLastReverse >= DelayTime){
			bIsWaiting = false;
			TimeSinceLastReverse = 0.f;
		}
	}
}

void ASimpleMovingPlatform::MovePlatform(float DeltaTime) {
	if (ShouldPlatformReturn()){
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (MoveDirection * MoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
		bIsWaiting = true;
	} else {
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void ASimpleMovingPlatform::RotatePlatform(float DeltaTime) {
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool ASimpleMovingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > MoveDistance;
}

float ASimpleMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(StartLocation, GetActorLocation());
}

