// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "MyBall.generated.h"

UCLASS()
class SLATEPROJ_API AMyBall : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    AMyBall();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* Sphere1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMeshComponent* StaticMesh1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystemComponent* Particle1;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};

