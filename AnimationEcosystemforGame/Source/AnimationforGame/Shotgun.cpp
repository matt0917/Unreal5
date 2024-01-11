// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"

// Sets default values
AShotgun::AShotgun()
	:WeaponSkeletalMeshComponent(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh")))
{
	WeaponSkeletalMeshComponent->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

