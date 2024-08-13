// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"



ATower::ATower()
	:LookAtDistanceRange(200.f),
	FireRange(300.f),
	FireRate(2.f)
{

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
}


void ATower::CheckFireCondition() 
{
	if (Tank && InActionRange(FireRange))
	{
		FireCannon();
	}
}

bool ATower::InActionRange(const float& DistanceRange) {
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	if (Distance <= FireRange){
		return true;
	}
	return false;
}