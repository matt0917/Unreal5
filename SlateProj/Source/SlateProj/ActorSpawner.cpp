// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorSpawner.h"
#include "MyBall.h"

float AActorSpawner::SMIN = -500.0f;
float AActorSpawner::SMAX = 500.0f;

// Sets default values
AActorSpawner::AActorSpawner()
	:MinX(SMIN), MaxX(SMAX), MinY(SMIN), MaxY(SMAX)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));

	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AActorSpawner::SpawnActor() const
{
	FVector SpawnLocation = GetActorLocation();

	// Generate random offsets for X and Y axes
	float RandomX = FMath::RandRange(MinX, MaxX);
	float RandomY = FMath::RandRange(MinY, MaxY);

	SpawnLocation.X += RandomX;
	SpawnLocation.Y += RandomY;

	const FRotator SpawnRotation = GetActorRotation();
	GetWorld()->SpawnActor<AMyBall>(SpawnLocation, SpawnRotation);
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

