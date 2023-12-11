// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProjectGameMode.h"
#include "ThirdPersonProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonProjectGameMode::AThirdPersonProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
