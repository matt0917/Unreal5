// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Tutorial/InputPlayer/InputCharacter.h"
#include "InputMappingContext.h"
#include "Tutorial/Data/InputConfigData.h"

// Sets default values
AInputCharacter::AInputCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInputCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem != nullptr)
		{
			// Add input context created in the editor
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(InputActions->Test, ETriggerEvent::Triggered, this, &AInputCharacter::TestAction);
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(InputActions->NewJump, ETriggerEvent::Triggered, this, &AInputCharacter::JumpAction);
	}
}

void AInputCharacter::TestAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, "Pressed input1 action", true, {2.0f, 2.0f});
}

void AInputCharacter::JumpAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, "Pressed Jump1 action", true, { 2.f, 2.f });
}


