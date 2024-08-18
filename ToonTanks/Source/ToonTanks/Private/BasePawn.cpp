// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "projectile.h"



// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(CapsuleComp);
	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Base Mesh"));
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));

	TurretBase->SetupAttachment(RootComponent);
	Turret->SetupAttachment(TurretBase);
	ProjectileSpawnPoint->SetupAttachment(Turret);

	Speed = 400.f;
}

void ABasePawn::RotateTurret(FVector LookAtTarget) 
{
	FVector ToTarget = LookAtTarget - Turret->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	Turret->SetWorldRotation(
			FMath::RInterpTo(Turret->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			25.f)
	);
}

void ABasePawn::FireCannon() 
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	// Visual/sound effects
	if (DeathParticles){
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticles,
			GetActorLocation(),
			GetActorRotation()
		);
	}
}





