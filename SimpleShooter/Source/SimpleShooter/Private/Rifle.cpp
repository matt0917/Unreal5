// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Kismet/GameplayStatics.h"


ARifle::ARifle()
{}

void ARifle::BeginPlay()
{}

void ARifle::Tick(float DeltaTime)
{}

void ARifle::PullTrigger()
{
	Super::PullTrigger();
	if(MuzzleFlashFX){
		RunVfx();
	}
}

void ARifle::RunVfx() 
{
	if (MuzzleSocketName.IsNone()) { return; }
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashFX, Mesh, MuzzleSocketName);
}

void ARifle::RunSfx() {}

