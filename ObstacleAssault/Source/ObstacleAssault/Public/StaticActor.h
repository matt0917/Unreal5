// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticActor.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AStaticActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticActor();

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category="Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category="Attributes")
	float DelayTime;

	UPROPERTY(EditAnywhere, DisplayName="Delay at Begin", Category = "Attributes")
	bool bDelayAtBegin;

	UPROPERTY()
	bool bIsWaiting;

	UPROPERTY()
	float TimeSinceLastReverse;
};
