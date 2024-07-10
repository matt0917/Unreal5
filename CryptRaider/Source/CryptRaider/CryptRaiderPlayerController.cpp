// Copyright Epic Games, Inc. All Rights Reserved.


#include "CryptRaiderPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"




void ACryptRaiderPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	AddInputMappingContexts();
} 


void ACryptRaiderPlayerController::AddInputMappingContexts() {
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		// Get the enhanced input systems
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)){
			// Add the movement mapping context
			if (MovementMappingContext){
				Subsystem->AddMappingContext(MovementMappingContext, 0); //priority 0
			}
		}
	}
}