// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "BasePawn.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	:MaxHealth(100.f), CurrentHealth(100.f), TargetHealth(100.f), InterpSpeed(5.f), MinHealthThreshold(4.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	//Define the GameMode so when the CurrentHealth becomes 0, call the ActorDied function in the GameMode
	ToonTankGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if the current Owner(Actor) is not destroyed and not hidden in the Game
	if (GetOwner() && !GetOwner()->IsHidden()){
		// Interpolate the health smoothly using FInterpTo
		CurrentHealth = FMath::FInterpTo(CurrentHealth, TargetHealth, DeltaTime, InterpSpeed);
		if (CurrentHealth < MinHealthThreshold && ToonTankGameMode) {
			ToonTankGameMode->ActorDied(GetOwner());
		}
	}
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser) 
{
	//UE_LOG(LogTemp, Warning, TEXT("GameMode: %s"), *ToonTankGameMode->GetName());
	// Calculate the new target health
	if (TargetHealth == MinHealthThreshold){
		TargetHealth = 0.f;
	} else {
		TargetHealth = CurrentHealth - (Damage * Cast<ABasePawn>(DamagedActor)->DamageRatio);
		// Clamp TargetHealth to ensure it does not go below the minimum health threshold
		if (TargetHealth < MinHealthThreshold){
			TargetHealth = FMath::Max(TargetHealth, MinHealthThreshold);
		}
	}
}