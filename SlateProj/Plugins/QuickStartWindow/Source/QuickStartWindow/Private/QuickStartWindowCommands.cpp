// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuickStartWindowCommands.h"

#define LOCTEXT_NAMESPACE "FQuickStartWindowModule"

void FQuickStartWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "QuickStartWindow", "Bring up QuickStartWindow window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
