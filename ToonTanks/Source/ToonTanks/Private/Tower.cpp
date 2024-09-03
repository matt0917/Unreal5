// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"



ATower::ATower()
	:LookAtDistanceRange(200.f),
	ShowHealthDistanceRange(1000.f),
	FireRange(300.f),
	FireRate(2.f)
{
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Turret HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
}

void ATower::BeginPlay() 
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true); 
}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank && InActionRange(LookAtDistanceRange))
	{
		RotateTurret(Tank->GetActorLocation());
	}

	if (HealthBar){
		if (Tank && InActionRange(ShowHealthDistanceRange)){
			FVector ToTarget = Tank->MainCamera->GetComponentLocation() - HealthBar->GetComponentLocation();
			FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
			RotateWidgetToTarget(HealthBar, LookAtRotation);
			HealthBar->SetVisibility(true);
		}
		else{
			HealthBar->SetVisibility(false);
		}
	}	
}

void ATower::HandleDestruction() 
{
	Super::HandleDestruction();
	Destroy();
}


void ATower::CheckFireCondition() 
{
	if(Tank == nullptr){
		return;
	}
	if(Tank && Tank->bAlive && InActionRange(FireRange))
	{
		FireCannon();
	}
}  

bool ATower::InActionRange(const float& DistanceRange) {
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	if (Distance <= DistanceRange){
		return true;
	}
	return false;
}

void ATower::RotateWidgetToTarget(UWidgetComponent* Widget, const FRotator& Rotator)
{
	Widget->SetWorldRotation(Rotator);
}