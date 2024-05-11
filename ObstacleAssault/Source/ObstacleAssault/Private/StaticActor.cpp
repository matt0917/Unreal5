// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticActor.h"

// Sets default values
AStaticActor::AStaticActor()
	:Health(100.f), DelayTime(2.f), TimeSinceLastReverse(0.f), bDelayAtBegin(false), bIsWaiting(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AStaticActor::BeginPlay() 
{
	Super::BeginPlay();

	bIsWaiting = bDelayAtBegin;
}



