// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBall.h"

// Sets default values
AMyBall::AMyBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creating default components
	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Ball1"));
	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Particle1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire1"));

	//Attahcing components and setting physics
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->SetSimulatePhysics(true);
	Sphere1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMesh1->AttachToComponent(Sphere1, FAttachmentTransformRules::KeepRelativeTransform);
	Particle1->AttachToComponent(StaticMesh1, FAttachmentTransformRules::KeepRelativeTransform);

	//member settings
	//Sphere1 radius
	Sphere1->SetSphereRadius(16.0f);
	//Static mesh
	StaticMesh1->SetRelativeLocation(FVector(0.0, 0.0, -12.0f));
	StaticMesh1->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	// Using Constructor Helpers to set StatickMesh1 with Sphere1
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereAsset1(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	StaticMesh1->SetStaticMesh(SphereAsset1.Object);

	//Using Constructor Helpers to set our Particle Comp with our Fire Particle Comp.
	const TCHAR* PPath = TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'");
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset1(PPath);
	if (ParticleAsset1.Succeeded())
	{
		Particle1->SetTemplate(ParticleAsset1.Object);
		UE_LOG(LogTemp, Warning, TEXT("Component found: %s"), PPath);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("No component found: %s"), PPath);
	}
}

// Called when the game starts or when spawned
void AMyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

