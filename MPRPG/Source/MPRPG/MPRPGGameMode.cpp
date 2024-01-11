// Copyright Epic Games, Inc. All Rights Reserved.

#include "MPRPGGameMode.h"
#include "MPRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMPRPGGameMode::AMPRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
