// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticActor.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingPlatform.generated.h"



UCLASS()
class OBSTACLEASSAULT_API ARotatingPlatform : public AStaticActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	class UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FVector RotateAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float SpinSpeedDegrees;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	float TotalDegreesRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 RotateRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float RotateVectorScaler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotatePlatform(float DeltaTime);
};
