// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATower();

	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, Category="Combat")
	float LookAtDistanceRange;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float FireRange;

private:
	TObjectPtr<class ATank> Tank;

	FTimerHandle FireRateTimerHandle;

	float FireRate;

	void CheckFireCondition();

	bool InActionRange(const float& DistanceRange);
};
