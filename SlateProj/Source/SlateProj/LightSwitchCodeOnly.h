// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "LightSwitchCodeOnly.generated.h"

UCLASS()
class SLATEPROJ_API ALightSwitchCodeOnly : public AActor
{
	GENERATED_BODY()
	
public:
	// point light
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class UPointLightComponent* PointLight1; //using class keyword is forward declaration of UPointLightComponent class
	// sphere
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	class USphereComponent* Sphere1;

	// Sets default values for this actor's properties
	ALightSwitchCodeOnly();

	// functions
	UFUNCTION()
	FLinearColor GetCurrentLightColor() const;

	UFUNCTION()
	void SetCurrentLightColor(const FLinearColor& NewColor);

	UFUNCTION()
	// called when something enters the sphere component
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// called when something leaves the sphere component
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// toggle light component's visibility
	UFUNCTION()
	void ToggleLight() const;

	// desired intensity for the light
	UPROPERTY(VisibleAnywhere, Category="Switch Variables")
	float DesiredIntensity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	static const FLinearColor DesiredColor;
	FLinearColor OutLightColor;
};
