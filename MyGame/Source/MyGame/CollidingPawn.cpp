// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "CollidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


DEFINE_LOG_CATEGORY(LogCollidingPawn);

// Sets default values
ACollidingPawn::ACollidingPawn()
	:MyParticleSystem(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"))),
	SphereComponent(CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"))),
	SphereVisual(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"))),
	SpringArm(CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"))),
	MainCamera(CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"))),
	MyMovementComponent(CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent")))
{
	RootComponent = SphereComponent;
	//SphereComponent->SetCollisionObjectType();
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	SphereComponent->SetMobility(EComponentMobility::Movable);

	SphereVisual->SetupAttachment(RootComponent);

	MyParticleSystem->SetupAttachment(SphereComponent);
	MyParticleSystem->bAutoActivate = false;
	MyParticleSystem->SetRelativeLocation(FVector(-20.f, 0.f, 20.f));

	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->CameraLagSpeed = 3.f;

	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Define MyMovementComponent is to update the RootComponent for changes.
	MyMovementComponent->UpdatedComponent = RootComponent;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem != nullptr)
		{
			// Add input context created in the editor
			Subsystem->AddMappingContext(DefaultInputMappingContext, 0);
		}
	}
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACollidingPawn::Move);
		Input->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ACollidingPawn::Turn);
		Input->BindAction(ParticleToggleAction, ETriggerEvent::Triggered, this, &ACollidingPawn::ParticleToggle);
	}
	else
	{
		UE_LOG(LogCollidingPawn, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return MyMovementComponent;
}

void ACollidingPawn::Move(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, "Move", true, {2.f, 2.f});
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add inputVector movement to the RootComponent
		MyMovementComponent->AddInputVector(ForwardDirection * MovementVector.Y);
		MyMovementComponent->AddInputVector(RightDirection * MovementVector.X);
	}
}

void ACollidingPawn::Turn(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, "Turn Camera", true, {2.f, 2.f});
	const FVector2D TurnAxisVector = Value.Get<FVector2D>();
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += TurnAxisVector.X;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (MyParticleSystem && MyParticleSystem->Template)
	{
		MyParticleSystem->ToggleActive();
	}
}



