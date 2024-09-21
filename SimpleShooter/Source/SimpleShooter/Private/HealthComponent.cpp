// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "ShooterCharacter.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	:MaxHealth(100.f), CurrentHealth(MaxHealth), TargetHealth(MaxHealth), InterpSpeed(5.f), MinHealthThreshold(4.f)
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

	Owner = Cast<AShooterCharacter>(GetOwner());
	if (Owner == nullptr) { return; }
	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	//Define the GameMode so when the CurrenHealth becomes 0, call the ActorDied function in the GameMode
	ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(this));
}



// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if the current Owner(Actor) is not destroyed and not hidden in the Game
	if (Owner && !Owner->IsDead() && !Owner->IsHidden()) {
		// Interpolate the health smoothly using FInterpTo
		CurrentHealth = FMath::FInterpTo(CurrentHealth, TargetHealth, DeltaTime, InterpSpeed);
		if (CurrentHealth < MinHealthThreshold && ShooterGameMode){
			ShooterGameMode->ActorDied(Owner);
		}
	}
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instrigator, AActor* DamageCauser) \
{
	// Calculate the new target Health
	if (TargetHealth == MinHealthThreshold){
		TargetHealth = 0.f;
	} else {
		TargetHealth = CurrentHealth - (Damage * Cast<AShooterCharacter>(DamagedActor)->DamageRatio);
		// Clamp TargetHealth to esnures it does not go below the minimum health threshold
		if (TargetHealth < MinHealthThreshold){
			TargetHealth = FMath::Max(TargetHealth, MinHealthThreshold);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("Current Health: %.2f"), TargetHealth));
}
