// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

protected:
	virtual void BeginPlay();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USpringArmComponent> MainCameraSpringArm;

private:
	//Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input", meta=(AllowPrivateAccess="true")); 
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta=(AllowPrivateAccess="true"));
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta=(AllowPrivateAccess="true"));
	TObjectPtr<UInputAction> RotateTurretAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta=(AllowPrivateAccess="true"));
	TObjectPtr<UInputAction> FireAction;

	TObjectPtr<APlayerController> TankPlayerController;

protected:
	//Functions for input actions
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void Fire(const FInputActionValue& Value);

	UFUNCTION()
	void RotateTurretByKey(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurnRate;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	APlayerController* GetTankPlayerController() const;
};
