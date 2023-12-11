// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateProjGameMode.h"
#include "SlateProjCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlateProjGameMode::ASlateProjGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
