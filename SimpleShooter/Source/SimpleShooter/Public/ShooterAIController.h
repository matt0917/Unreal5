// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

	AShooterAIController();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime);

	UFUNCTION()
	void StopAI();

private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius;


};
