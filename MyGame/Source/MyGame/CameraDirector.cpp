// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

	SwitchTarget();
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACameraDirector::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem != nullptr)
		{
			// Add input context created in the editor
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(CamSwitchAction, ETriggerEvent::Triggered, this, &ACameraDirector::SwitchTarget);
	}

}

void ACameraDirector::SwitchTarget()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if ((PlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
		{
			PlayerController->SetViewTargetWithBlend(CameraOne, 0.75f);
		}
		else if ((PlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
		{
			PlayerController->SetViewTarget((CameraTwo));
		}
	}
}

