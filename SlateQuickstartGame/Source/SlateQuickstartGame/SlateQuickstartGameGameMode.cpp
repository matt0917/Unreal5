// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateQuickstartGameGameMode.h"
#include "SlateQuickstartGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlateQuickstartGameGameMode::ASlateQuickstartGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
