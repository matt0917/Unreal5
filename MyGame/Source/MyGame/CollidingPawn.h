// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollidingPawnMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCollidingPawn, Log, All) //Log is a Log level, All is Compile time verbosity

UCLASS()
class MYGAME_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* MyParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SphereVisual;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere)
	UCollidingPawnMovementComponent* MyMovementComponent;

protected:
	//Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input")
	class UInputAction* ParticleToggleAction;

	//functions of Input Actions
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Turn(const FInputActionValue& Value);

	UFUNCTION()
	void ParticleToggle();


public:
	// Override the function to replace it with MyMovementComponent class
	virtual UPawnMovementComponent* GetMovementComponent() const override;
};
