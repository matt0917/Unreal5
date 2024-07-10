// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapTriggerBoxComponent.h"


UOverlapTriggerBoxComponent::UOverlapTriggerBoxComponent()
	:AcceptableTag(FName(TEXT("OverlapProp")))
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UOverlapTriggerBoxComponent::BeginPlay() {
	//OnComponentBeginOverlap.AddDynamic(this, &UOverlapTriggerBoxComponent::OnOverlapBegin);
}


void UOverlapTriggerBoxComponent::SetMover(UMover* _Mover) {
	Mover = _Mover;
}

void UOverlapTriggerBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr){
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Unlocking"));
		UPrimitiveComponent* ActorRootComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (ActorRootComponent != nullptr){
			ActorRootComponent->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else{
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Relocking"));
		Mover->SetShouldMove(false);
	}
}

AActor* UOverlapTriggerBoxComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor : Actors) {
		if (Actor->ActorHasTag(AcceptableTag)) {
			return Actor;
		}
	}
	return nullptr;
}


void UOverlapTriggerBoxComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(AStaticMeshActor::StaticClass())){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Overlapped with: %s"), *OtherActor->GetActorNameOrLabel()));

	}
}

