// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitchBoth.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"



// Sets default values
ALightSwitchBoth::ALightSwitchBoth()
	:PointLight1(CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"))),
	Sphere1(CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"))),
	DesiredIntensity(3000.f)
{
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibility(true);
	RootComponent = PointLight1;

	Sphere1->InitSphereRadius(250.f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchBoth::OnOverlapBegin);
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchBoth::OnOverlapEnd);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightSwitchBoth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitchBoth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightSwitchBoth::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchBoth::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchBoth::ToggleLight()
{
	//PointLight1->ToggleVisibility();
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Color"));
	if(PointLight1->IsVisible())
	{
		PointLight1->SetLightColor(FColor::Red);
	}
}

