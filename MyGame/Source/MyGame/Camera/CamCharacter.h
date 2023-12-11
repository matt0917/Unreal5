// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Logging/LogMacros.h"
#include "CamCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All) //Log is a Log level, All is Compile time verbosity

UCLASS()
class MYGAME_API ACamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACamCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Arrow Component for the Camera shoulder viewpoint location
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UArrowComponent* CameraRShoulderLocation;

	// Arrow Component for the Camera Origin viewpoint location
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UArrowComponent* CameraOriginLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

	// enhanced input
	// Input MappingContext
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputMappingContext* InputMapping;

	// Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* CamMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Factors")
	float Alpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Factors")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Factors")
	float EasingExponent;

	float StartAlpha;
	float TargetAlpha;
	float CurrentLerpTime;

	// SprintArm component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	// Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta=(AllowPrivateAccess="true"))
	class UInputAction* MoveAction;

	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input", meta=(AllowPrivateAccess="true"))
	class UInputAction* LookAction;

protected:
	void MoveCamToShoulder(void);
	void MoveCamToOrigin(void);

	void MoveCamBetweenTwoLocations(void);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
};
