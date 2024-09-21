// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Navigation/PathFollowingComponent.h"
#include "ShooterCharacter.h"


AShooterAIController::AShooterAIController()
	:AcceptanceRadius(200.f){}


void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Stop AI when the controlled character is dead by getting the dead status value sets in the ShooterCharacter class
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr || Cast<AShooterCharacter>(ControlledPawn)->IsDead()) {
		StopAI();
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (LineOfSightTo(PlayerPawn)){
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, AcceptanceRadius);
	} else {
		StopAI();
	}
}


void AShooterAIController::StopAI()
{
	ClearFocus(EAIFocusPriority::Gameplay);
	StopMovement();	
}