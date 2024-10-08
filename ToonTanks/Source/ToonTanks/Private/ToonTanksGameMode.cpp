// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


AToonTanksGameMode::AToonTanksGameMode()
	:StartDelay(3.f)
{}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("IsAttacking: %s"), *DeadActor->GetActorNameOrLabel()));

	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController){
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)){
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		// check the tower is zero and it means GameOver if it is.
		if (TargetTowers == 0){
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay() 
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart() 
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	// disable input handle at the begining of the game
	if (ToonTanksPlayerController){
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount() {
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(
		this,
		ATower::StaticClass(),
		Towers
	);
	return Towers.Num();
}
