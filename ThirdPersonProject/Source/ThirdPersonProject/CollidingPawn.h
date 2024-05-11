// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CollidingPawnMovementComponent.h"
#include "CollidingPawn.generated.h"

class UInputActions;
class UInputMappingContext;

UCLASS()
class THIRDPERSONPROJECT_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ParticleToggleAction;
public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// particles
	UFUNCTION()
	void ToggleParticles();

	UFUNCTION()
	void Move(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// pawn에는 현재 pawn이 사용중인 pawn movement component에 접근할 수 있도록 하는데 사용하는 함수가 있습니다. 그함수를 override해서 custom pawn movement를 return하도록 해야 합니다. 
	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCollidingPawnMovementComponent* CustomMoveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* Particles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* MainCam;

};
