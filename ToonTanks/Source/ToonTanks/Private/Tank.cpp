// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
	:TurnRate(45.f)
{
	MainCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCamera SpringArm"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));

	MainCameraSpringArm->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(MainCameraSpringArm);
}

void ATank::BeginPlay() 
{
	Super::BeginPlay();

	if (PlayerController = Cast<APlayerController>(GetController()))
	{
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem){
			Subsystem->AddMappingContext(DefaultInputMappingContext, 0);
		}
	}

}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (TObjectPtr<UEnhancedInputComponent> Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
	}
	if (TObjectPtr<UEnhancedInputComponent> Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		Input->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
	if (TObjectPtr<UEnhancedInputComponent> Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		Input->BindAction(RotateTurretAction, ETriggerEvent::Triggered, this, &ATank::RotateTurretByKey);
	}

	
}

void ATank::Move(const FInputActionValue& Value){
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add inputVector movement to the RootComponent
		double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalOffset(ForwardDirection * MovementVector.Y * Speed * DeltaTime, true);

		FRotator DeltaRotation = FRotator::ZeroRotator;
		DeltaRotation.Yaw = MovementVector.X * TurnRate * DeltaTime;
		AddActorLocalRotation(DeltaRotation, true);
	}
}

void ATank::Fire(const FInputActionValue& Value) 
{
	if (Value.Get<float>() > 0.1f){
		FireCannon();
	}
} 

void ATank::RotateTurretByKey(const FInputActionValue& Value) {
}

void ATank::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (PlayerController){
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}

