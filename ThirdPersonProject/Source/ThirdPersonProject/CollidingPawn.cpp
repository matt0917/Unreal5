// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ThirdPersonProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
	:Particles(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MoveParticles"))),
	SpringArm(CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraSpringArm"))),
	MainCam(CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"))),
	CustomMoveComponent(CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMoveComponent")))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create sphere
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = SphereComponent;

	// Create and position a mesh component so I can see where my sphere is
	UStaticMeshComponent* SphereVisual{CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"))};
	SphereVisual->SetupAttachment(RootComponent);
	// find a sphere static mesh in Content by using ConstructorHelpers::FObjectFinder<typename>(TEXT("object name"))
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	//Particles
	Particles->SetupAttachment(SphereVisual);
	Particles->bAutoActivate = false;
	Particles->SetRelativeLocation(FVector(-20.f, 0.f, 0.f));
	// find a default fire particles from startContents  this is better to be done in a blueprint
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (ParticleAsset.Succeeded())
	{
		Particles->SetTemplate(ParticleAsset.Object);
	}

	//SpringArm
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	//MainCam
	MainCam->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// set movement component to tell it to update the root
	CustomMoveComponent->UpdatedComponent = RootComponent;
}

// override GetMovementComponent of Pawn member function
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return CustomMoveComponent;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
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
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACollidingPawn::Move);

		// Toggle Particle Action
		EnhancedInputComponent->BindAction(ParticleToggleAction, ETriggerEvent::Triggered, this, &ACollidingPawn::ToggleParticles);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACollidingPawn::ToggleParticles()
{
	if (Particles && Particles->Template)
	{
		Particles->ToggleActive();
	}
}

void ACollidingPawn::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


