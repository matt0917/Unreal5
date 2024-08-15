// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	:MaxHealth(100.f), Health(0.f)
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

	Health = MaxHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	//Define the GameMode so when the Health becomes 0, call the ActorDied function in the GameMode
	ToonTankGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser) 
{
	//UE_LOG(LogTemp, Warning, TEXT("GameMode: %s"), *ToonTankGameMode->GetName());
	Health -= Damage;
	//UE_LOG(LogTemp, Warning, TEXT("Health: %.2f"), Health);
	if (Health <= 0.f && ToonTankGameMode){
		ToonTankGameMode->ActorDied(DamagedActor);
	}

}