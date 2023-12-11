// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuickStartWindowStyle.h"

class FQuickStartWindowCommands : public TCommands<FQuickStartWindowCommands>
{
public:

	FQuickStartWindowCommands()
		: TCommands<FQuickStartWindowCommands>(TEXT("QuickStartWindow"), NSLOCTEXT("Contexts", "QuickStartWindow", "QuickStartWindow Plugin"), NAME_None, FQuickStartWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};