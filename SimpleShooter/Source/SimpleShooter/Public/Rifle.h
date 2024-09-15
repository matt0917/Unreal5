// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ARifle : public AGun
{
	GENERATED_BODY()

public:
	ARifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PullTrigger() override;
	virtual void RunVfx() override;
	virtual void RunSfx() override;
};
