// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AToonTanksGameMode();

	void ActorDied(AActor* DeadActor);
	
protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	class AToonTanksPlayerController* ToonTanksPlayerController;

	UPROPERTY(EditDefaultsOnly, Category="Custom Property")
	float StartDelay;

	void HandleGameStart();
};
