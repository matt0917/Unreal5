// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InputActionValue.h"
#include "Grabber.generated.h"


class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
class APawn;
class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FRotator PreviousRotation;
	UWorld* CurrentWorld;
	APawn* Player;
	
	UPROPERTY(EditAnywhere, Category = "SweepShape")
	float MaxEnd;
	UPROPERTY(EditAnywhere, Category = "SweepShape")
	float SphereRad;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float HoldDistance;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* GrabMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

public:
	UFUNCTION(BlueprintCallable, Category="Functions")
	void Grab(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category="Functions")
	void Release();

private:
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	bool GetGrabbableToReach(FHitResult& OutHitResult) const;
};
