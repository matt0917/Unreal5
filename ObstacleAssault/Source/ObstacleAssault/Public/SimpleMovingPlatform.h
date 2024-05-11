// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticActor.h"
#include "SimpleMovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API ASimpleMovingPlatform : public AStaticActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	FVector PlatformVelocity;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MoveDistance;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	FRotator RotationVelocity;

	UPROPERTY()
	FVector StartLocation;;

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;
	float GetDistanceMoved() const;
};
