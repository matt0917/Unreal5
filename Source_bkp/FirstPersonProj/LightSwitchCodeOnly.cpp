// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchCodeOnly.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitchCodeOnly::ALightSwitchCodeOnly()
	:PointLight1(CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"))),
	Sphere1(CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"))),
	DesiredIntensity(3000.f)
{
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibility(true);
	PointLight1->SetLightColor(FColor::Blue);
	RootComponent = PointLight1;

	Sphere1->InitSphereRadius(250.f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, ALightSwitchCodeOnly::OnOverlapBegin);
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchCodeOnly::OnOverlapEnd);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightSwitchCodeOnly::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALightSwitchCodeOnly::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchCodeOnly::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchCodeOnly::ToggleLight()
{
	//PointLight1->ToggleVisibility();
}

// Called every frame
void ALightSwitchCodeOnly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

