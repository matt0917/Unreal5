// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
	:MoveOffset(FVector::Zero()), MoveTime(4.f), DelayTime(1.0f), TimeElapsed(0.0f), ShouldMove(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (Owner){
		StartLocation = Owner->GetActorLocation();
		EndLocation = StartLocation + MoveOffset;
	} else {
		UE_LOG(LogTemp, Error, TEXT("Owner is null in BeginPlay."));
	}
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner) {
		const float Speed = FVector::Distance(StartLocation, EndLocation) / MoveTime;
		const FVector CurrentLocation = Owner->GetActorLocation();
		if (ShouldMove) {
			TimeElapsed += DeltaTime;
			if (TimeElapsed < DelayTime){
				return;
			}
			const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, EndLocation, DeltaTime, Speed);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *NewLocation.ToCompactString());
			Owner->SetActorLocation(NewLocation);
			if (NewLocation == EndLocation){
				TimeElapsed = 0.0f;
				ShouldMove = false;
			}
		}
		else {
			TimeElapsed = 0.0f; //reset the value so when shouldMove is true again, restart elapsing time from 0.f
			const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, Speed);
			Owner->SetActorLocation(NewLocation);
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Owner is null in TickComponent."));
	}
}

void UMover::SetShouldMove(const bool& bShouldMove) {
	ShouldMove = bShouldMove;
}

