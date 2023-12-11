// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuickStartWindow.h"
#include "QuickStartWindowStyle.h"
#include "QuickStartWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SQuickStartWindowMenu.h"

static const FName QuickStartWindowTabName("QuickStartWindow");

#define LOCTEXT_NAMESPACE "FQuickStartWindowModule"

void FQuickStartWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuickStartWindowStyle::Initialize();
	FQuickStartWindowStyle::ReloadTextures();

	FQuickStartWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuickStartWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuickStartWindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQuickStartWindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuickStartWindowTabName, FOnSpawnTab::CreateRaw(this, &FQuickStartWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FQuickStartWindowTabTitle", "QuickStartWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FQuickStartWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FQuickStartWindowStyle::Shutdown();

	FQuickStartWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuickStartWindowTabName);
}

TSharedRef<SDockTab> FQuickStartWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	TSharedRef<SDockTab> MainTab =
	SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SQuickStartWindowMenu)
		];
	
	return MainTab;
}

void FQuickStartWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(QuickStartWindowTabName);
}

void FQuickStartWindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FQuickStartWindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FQuickStartWindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuickStartWindowModule, QuickStartWindow)