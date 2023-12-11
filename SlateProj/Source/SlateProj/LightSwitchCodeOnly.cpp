// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitchCodeOnly.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Light.h"


const FLinearColor ALightSwitchCodeOnly::DesiredColor = FLinearColor(1.0f, 0.0f, 0.0f);

// Sets default values
ALightSwitchCodeOnly::ALightSwitchCodeOnly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DesiredIntensity = 6000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->bVisualizeComponent = true;
	RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchCodeOnly::OnOverlapBegin);
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchCodeOnly::OnOverlapEnd);
}

FLinearColor ALightSwitchCodeOnly::GetCurrentLightColor() const
{
	return PointLight1->LightColor;
}

void ALightSwitchCodeOnly::SetCurrentLightColor(const FLinearColor& NewColor)
{
	PointLight1->SetLightColor(NewColor);
}

void ALightSwitchCodeOnly::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		PointLight1->SetLightColor(DesiredColor);
	}
}

void ALightSwitchCodeOnly::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		PointLight1->SetLightColor(OutLightColor);
	}
}

void ALightSwitchCodeOnly::ToggleLight() const
{
	PointLight1->ToggleVisibility();
}

// Called when the game starts or when spawned
void ALightSwitchCodeOnly::BeginPlay()
{
	Super::BeginPlay();
	OutLightColor = GetCurrentLightColor();
	UE_LOG(LogTemp, Warning, TEXT("Color - R: %f, G: %f, B: %f, A: %f"), OutLightColor.R, OutLightColor.G, OutLightColor.B, OutLightColor.A);
}

// Called every frame
void ALightSwitchCodeOnly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

