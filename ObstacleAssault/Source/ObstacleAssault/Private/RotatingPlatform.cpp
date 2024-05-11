// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
ARotatingPlatform::ARotatingPlatform()
    :RotateAxis(FVector(0.0f, 0.0f, 1.0f)), SpinSpeedDegrees(5.f), TotalDegreesRotated(0.f), RotateRound(1), RotateVectorScaler(-1.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RotateMesh"));
    PlatformMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    float TotalDegreesTarget = static_cast<float>(RotateRound) * 360.f;

    if (!bIsWaiting && TotalDegreesRotated < TotalDegreesTarget) {
        RotatePlatform(DeltaTime);
    }
    else if(!bIsWaiting && TotalDegreesRotated >= TotalDegreesTarget){
        // Optionally preform some action when target is reached
        bIsWaiting = true;
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Rotation Target Reached!"));
    }
    else {
        TimeSinceLastReverse += DeltaTime;
        if (TimeSinceLastReverse >= DelayTime) {
            bIsWaiting = false;
            TimeSinceLastReverse = 0.f;
            // Toggle between start and end positions
            RotateAxis *= RotateVectorScaler;
            TotalDegreesRotated = 0.f;
        }
    }
}

void ARotatingPlatform::RotatePlatform(float DeltaTime) 
{
    if (PlatformMesh) {
        // Existing rotation plus additional rotation to be added this frame
        const float SpinSpeedRadians = FMath::DegreesToRadians(SpinSpeedDegrees);
        float DeltaRotation = DeltaTime * SpinSpeedRadians; // SpinSpeed should be in radians/second
        // Convert radians to degrees for total rotation tracking
        TotalDegreesRotated += FMath::RadiansToDegrees(DeltaRotation);

        // Get the current rotation of the mesh
        FQuat CurrentRotation = PlatformMesh->GetRelativeRotation().Quaternion();
        // Create a quaternion representing the rotation to add this frame
        FQuat RotationToAdd = FQuat(RotateAxis, DeltaRotation);
        // Combine the current rotation with the additional rotation
        FQuat NewRotation = CurrentRotation * RotationToAdd;

        // Normalize the quaternion to avoid floating point errors accumulating over time
        NewRotation.Normalize();

        // Apply the new rotation to the mesh
        PlatformMesh->SetRelativeRotation(NewRotation);
    }
}

