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

protected:
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, Category="Custom Properties")
	float LookAtDistanceRange;

private:
	TObjectPtr<class ATank> Tank;
};
