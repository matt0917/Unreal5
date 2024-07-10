// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CryptRaiderPlayerController.generated.h"

class UInputMappingContext;
class AController;

/**
 *
 */
UCLASS()
class CRYPTRAIDER_API ACryptRaiderPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MovementMappingContext;

	void AddInputMappingContexts();
protected:

	virtual void BeginPlay() override;
};
