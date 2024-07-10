// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_PropComponent.h"
#include "CryptRaiderCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UTP_PropComponent::UTP_PropComponent() 
: PropOffset(FVector(60.0f, 0.0f, 10.0f)) {}



bool UTP_PropComponent::AttachProp(ACryptRaiderCharacter* TargetCharacter) {
	Character = TargetCharacter;

	// Check that the character is valid, and has no prop component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UTP_PropComponent>()) {
		return false;
	}

	// Attach the prop to the Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, Character->PropAttachPoint);

	// add the prop as an instance component to the character
	Character->AddInstanceComponent(this);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController())) {
		// Add action mapping for this prop and bind correspondent action
	}

	return true;
}

void UTP_PropComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (Character == nullptr) {
		return;
	}

	// remove the custom mapping context here
}



