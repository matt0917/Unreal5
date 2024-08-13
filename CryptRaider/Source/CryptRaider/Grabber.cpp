// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
	:PreviousRotation(FRotator::ZeroRotator), SphereRad(20.f), MaxEnd(500.f), HoldDistance(200.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	CurrentWorld = GetWorld();
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APawn>(GetOwner());
	if (Player == nullptr || Player->GetController() == nullptr) {
		return;
	}
	
	// Mapping context and action binding
	if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(GrabMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) {
			// Bind the InteractAction of start
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &UGrabber::Grab);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) {
			// Bind the InteractAction of completed
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &UGrabber::Release);
		}
	}

	PreviousRotation = GetComponentRotation();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FRotator CurrentRotation = GetComponentRotation();
	//if (CurrentRotation != PreviousRotation){
	//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, (TEXT("%s"), CurrentRotation.ToCompactString()));
	//	PreviousRotation = CurrentRotation;
	//}

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr){
			return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr){
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(
			TargetLocation,
			GetComponentRotation()
		);
	}
}


void UGrabber::Grab(const FInputActionValue& Value){

	//const FString CurrentValue = Value.Get<bool>() ? TEXT("True!!") : TEXT("False!!");
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, CurrentValue);
	if (CurrentWorld) {
		//double TimeSeconds = CurrentWorld->GetTimeSeconds();
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, FString::Printf(TEXT("Current time: %f"), TimeSeconds));
		UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
		if (PhysicsHandle == nullptr) {
			return;
		}

		FHitResult HitResult;
		bool HasHit = GetGrabbableToReach(HitResult);

		if (HasHit) {
			AActor* Actor = HitResult.GetActor();
			const FString& actorLabel = Actor->GetActorNameOrLabel();
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, actorLabel);

			// Make sure actor is detached from any other actor rootcomponent such as overlapped actor
			if (Actor->GetAttachParentActor() != nullptr){
				Actor->Tags[0] = FName("NoTag");
				Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Get simulation Back"));
			} else {
				if (Actor->Tags[0] == FName("NoTag")){
					Actor->Tags[0] = FName("OverlapProp");
				}
			}

			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			// set physics back again if it was removed from a previous event with other overlapped actor moving together.
			if (!HitComponent->IsSimulatingPhysics()){
				HitComponent->SetSimulatePhysics(true);
			}
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				HitComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation()
			);
		}
	}
}

void UGrabber::Release() {
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, FString::Printf(TEXT("Released")));
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr){
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() !=nullptr){
		PhysicsHandle->ReleaseComponent();
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const {
	// define Grabbing handle component
	UPhysicsHandleComponent* GrabHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (GrabHandle == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a PhysicsHandleComponent"))
	}
	return GrabHandle;
}

bool UGrabber::GetGrabbableToReach(FHitResult& OutHitResult) const {
	FVector StartLocation = GetComponentLocation();
	FVector EndLocation = StartLocation + (GetForwardVector() * MaxEnd);
	DrawDebugDirectionalArrow(CurrentWorld, StartLocation, EndLocation, 10.f, FColor::Cyan, false, -1.f);

	FQuat Rotation = FQuat::Identity;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRad);
	FCollisionQueryParams CollisionParams = FCollisionQueryParams::DefaultQueryParam;

	bool HasHit = CurrentWorld->SweepSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		Rotation,
		ECC_GameTraceChannel2, // get this ECC value from "project folder > Config > DefaultEngine.ini
		CollisionShape,
		CollisionParams
	);

	if (HasHit) {
		DrawDebugSphere(CurrentWorld, OutHitResult.ImpactPoint, 10.f, 24,
			FColor::Red, false, 1.0f);
	}

	return HasHit;
}



