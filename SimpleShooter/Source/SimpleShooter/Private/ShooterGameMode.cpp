// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "EnemyCharacter.h"


AShooterGameMode::AShooterGameMode() {}

void AShooterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerCharacter) {
		PlayerCharacter->HandleDestruction();
	} else if(AEnemyCharacter* DestroyedActor = Cast<AEnemyCharacter>(DeadActor)) {
		DestroyedActor->HandleDestruction();
	}
}

void AShooterGameMode::BeginPlay() 
{
	Super::BeginPlay();

	HandleGameStart();
}


void AShooterGameMode::HandleGameStart() 
{
}






