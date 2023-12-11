// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ActorSpawner.generated.h"

UCLASS()
class SLATEPROJ_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	static float SMIN;
	static float SMAX;
	
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

	UFUNCTION()
	void SpawnActor() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner Variable")
	float MinX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Variable")
	float MaxX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Variable")
	float MinY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Variable")
	float MaxY;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
