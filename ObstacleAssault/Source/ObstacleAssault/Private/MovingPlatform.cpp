// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
	:Speed(3.f), StartPosition(FVector::ZeroVector), EndPosition(FVector::ZeroVector), CurrentTarget(FVector::ZeroVector)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent( CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

	// Initialize the mesh to move
	OscillatingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OscillatingMesh"));
	OscillatingMesh->SetupAttachment(RootComponent);

#if WITH_EDITOR
	// Initialize the markers
	StartMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartMarker"));
	StartMarker->SetupAttachment(RootComponent);
	StartMarker->SetMobility(EComponentMobility::Movable);

	EndMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndMarker"));
	EndMarker->SetupAttachment(RootComponent);
	EndMarker->SetMobility(EComponentMobility::Movable);
#endif
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartPosition = StartMarker->GetComponentLocation();
	EndPosition = EndMarker->GetComponentLocation();
	CurrentTarget = EndPosition;

	if (StartMarker){
		StartMarker->DestroyComponent();
	}
	if (EndMarker){
		EndMarker->DestroyComponent();
	}

	ElapsedTime = 0.0f;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsWaiting){
		Move(DeltaTime);
	}
	else{
		TimeSinceLastReverse += DeltaTime;
		if(TimeSinceLastReverse >= DelayTime){
			bIsWaiting = false;
			TimeSinceLastReverse = 0.f;
			// Toggle between start and end positions
			CurrentTarget = (CurrentTarget.Equals(StartPosition, 0.1f)) ? EndPosition : StartPosition;
		}
	}
}

void AMovingPlatform::Move(float DeltaTime) 
{
	FVector CurrentPosition = OscillatingMesh->GetComponentLocation();
	if (FVector::Dist(CurrentPosition, CurrentTarget) < 10.f){
		bIsWaiting = true; // Start waiting when close to the target
	}
	else{
		ElapsedTime += DeltaTime;
		float SineWave = sin(ElapsedTime * (Speed*0.01) * PI * 2); // Generates a value between -1 and 1
		FVector NewPosition = FMath::Lerp(StartPosition, EndPosition, (SineWave + 1.0f) / 2.0f); // Map sine -1:1 to 0:1
		OscillatingMesh->SetWorldLocation(NewPosition);
	}
}

