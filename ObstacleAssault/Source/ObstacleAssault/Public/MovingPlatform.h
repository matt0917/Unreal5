// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AStaticActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	UFUNCTION()
	void Move(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	class UStaticMeshComponent* OscillatingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Markers")
	class UStaticMeshComponent* StartMarker;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Markers")
	class UStaticMeshComponent* EndMarker;

private:
	UPROPERTY()
	float ElapsedTime;

	UPROPERTY()
	FVector StartPosition;

	UPROPERTY()
	FVector EndPosition;

	UPROPERTY()
	FVector CurrentTarget;
};
