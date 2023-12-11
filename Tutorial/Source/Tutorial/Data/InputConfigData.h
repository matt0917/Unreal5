// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Test;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* NewJump;
};
