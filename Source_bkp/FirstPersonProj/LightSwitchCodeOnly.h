// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitchCodeOnly.generated.h"

UCLASS()
class FIRSTPERSONPROJ_API ALightSwitchCodeOnly : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class UPointLightComponent* PointLight1;

	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class USphereComponent* Sphere1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch Variables", meta = (AllowPrivateAccess = "true"))
	float DesiredIntensity;

public:	
	// Sets default values for this actor's properties
	ALightSwitchCodeOnly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when an actor or a component enter to a component of this actor
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 otherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	// Called when an actor or a component outside of a component of this actor
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// Toggle this light visibility
	UFUNCTION()
	void ToggleLight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
