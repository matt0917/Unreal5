// Fill out your copyright notice in the Description page of Project Settings.


#include "CamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
ACamCharacter::ACamCharacter()
	:CameraRShoulderLocation{ CreateDefaultSubobject<UArrowComponent>(TEXT("CameraRShoulderLocation")) },
	CameraOriginLocation{ CreateDefaultSubobject<UArrowComponent>(TEXT("CameraOriginLocation")) },
	CameraComp{ CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp")) },
	Alpha{ 0.f }, Duration{ 1.f }, EasingExponent{2.f},
	SpringArmComp{CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"))}
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Don't rotate when the controller rotates. Let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; //Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 10.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;


 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Attach USpringComponent to the SkeletalMesh component
	SpringArmComp->SetupAttachment(GetMesh());

	// Attach the Camera to the SpringArmComponent
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	// Attach class Components to the default character's Skeletal Mesh Component.
	CameraRShoulderLocation->SetupAttachment(GetMesh());
	CameraOriginLocation->SetupAttachment(GetMesh());

	// Setting definition of the SpringArmComp
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = 120.f;
}

// Called when the game starts or when spawned
void ACamCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//Get local player subSystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void ACamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentLerpTime < Duration)
	{
		CurrentLerpTime += DeltaTime;
		Alpha = FMath::InterpEaseInOut(StartAlpha, TargetAlpha, CurrentLerpTime / Duration, EasingExponent);
		MoveCamBetweenTwoLocations();
	}
}

// Called to bind functionality to input
void ACamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Name of this: '%s'"), *GetNameSafe(this));
		// Cam switch space between origin and shoulder of the character
		Input->BindAction(CamMove, ETriggerEvent::Completed, this, &ACamCharacter::MoveCamToShoulder);
		Input->BindAction(CamMove, ETriggerEvent::Triggered, this, &ACamCharacter::MoveCamToOrigin);

		// Moving
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACamCharacter::Move);

		// Looking
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACamCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this)); //Safe means Null gives None.
	}
}

void ACamCharacter::MoveCamToShoulder()
{
	StartAlpha = Alpha;
	TargetAlpha = 0.0f;
	CurrentLerpTime = 0.0f;
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Blue, "Pull back cam", true, {1.5f, 1.5f});
}

void ACamCharacter::MoveCamToOrigin()
{
	StartAlpha = Alpha;
	TargetAlpha = 1.0f;
	CurrentLerpTime = 0.0f;
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, "Move shoulder cam", true, {1.5f, 1.5f});
}

void ACamCharacter::MoveCamBetweenTwoLocations()
{
	// Ensure Alpha is clamped between 0 and 1
	const float InterpolationAlpha = FMath::Clamp(Alpha, 0.0f, 1.0f);

	const FVector StartLocation = CameraOriginLocation->GetRelativeLocation();
	const FVector EndLocation = CameraRShoulderLocation->GetRelativeLocation();

	// Linearly interpolate the location for simplicity
	const FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, InterpolationAlpha);

	SpringArmComp->SetRelativeLocation(NewLocation);
}

void ACamCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Move"));
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation{0, Rotation.Yaw, 0};

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACamCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Purple, TEXT("Look"));

		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
