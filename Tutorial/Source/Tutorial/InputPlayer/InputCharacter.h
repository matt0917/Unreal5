// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputCharacter.generated.h"

UCLASS()
class TUTORIAL_API AInputCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInputCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	//class UInputAction* Test;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	//class UInputAction* NewJump;

	UFUNCTION() //Expose this to UE Reflection system
	void TestAction();

	void JumpAction(); //Jump use in the class

	// Instead of using 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UInputConfigData* InputActions;
};
