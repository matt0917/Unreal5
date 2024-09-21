// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
	:WeaponType(EWeaponType::Medium), MaxRange(2000.f), Damage(1.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("You have been shot!"));

	if (Mesh == nullptr || MuzzleSocketName.IsNone()){
		return;
	}

	// Get Controller of this gun
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) { return;  };
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) { return; }

	FVector StartLocation;
	FRotator StartRotation;
	//OwnerController->GetPlayerViewPoint(StartLocation, StartRotation);
	StartLocation = Mesh->GetSocketLocation(MuzzleSocketName);
	StartRotation = Mesh->GetSocketRotation(MuzzleSocketName);
	FVector EndLocation = StartLocation + StartRotation.Vector() * MaxRange;

	FHitResult HitResult;

	// Check Hit Result by calling SweepSingleByChannel
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1
	);
	if (!bHit) { return; }


	if (ImpactFx){
		FVector HitFacingDirection = -StartRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFx, HitResult.Location, HitFacingDirection.Rotation());
		FPointDamageEvent DamageEvent(Damage, HitResult, HitFacingDirection, nullptr);
		if (AActor* HitActor = HitResult.GetActor()){
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Hit on: %s"), *HitResult.GetActor()->GetActorNameOrLabel()));
		}
	}

	//DrawDebugPoint(
	//	GetWorld(), HitResult.Location,
	//	20, FColor::Red, false, 1.f);
	
}

