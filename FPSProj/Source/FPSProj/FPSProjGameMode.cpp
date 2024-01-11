// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProjGameMode.h"
#include "FPSProjCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSProjGameMode::AFPSProjGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
