// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TankPlayerStart.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TOONTANKS_API ATankPlayerStart : public APlayerStart
{
	GENERATED_BODY()

	ATankPlayerStart(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category= "Custom Properties")
	float CapsuleWidth;

	UPROPERTY(EditAnywhere, Category = "Custom Properties")
	float CapsuleHeight;

};
