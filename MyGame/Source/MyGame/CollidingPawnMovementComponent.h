// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UCollidingPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UCollidingPawnMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Variable")
	float MoveMultiplier;
};
