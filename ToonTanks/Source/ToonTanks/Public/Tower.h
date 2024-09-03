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
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category="Combat")
	float LookAtDistanceRange;

	UPROPERTY(EditAnywhere, Category ="UI")
	float ShowHealthDistanceRange;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float FireRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	class UWidgetComponent* HealthBar;

private:
	TObjectPtr<class ATank> Tank;

	FTimerHandle FireRateTimerHandle;

	float FireRate;

	void CheckFireCondition();

	bool InActionRange(const float& DistanceRange);

	void RotateWidgetToTarget(UWidgetComponent* Widget, const FRotator& Rotator);
};
