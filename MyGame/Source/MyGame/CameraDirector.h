// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "CameraDirector.generated.h"

UCLASS()
class MYGAME_API ACameraDirector : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CameraSwitchTarget)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSwitchTarget)
	AActor* CameraTwo;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* CamSwitchAction;

protected:
	void SwitchTarget();
};
