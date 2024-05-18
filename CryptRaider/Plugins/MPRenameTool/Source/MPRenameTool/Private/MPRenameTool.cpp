#include "MPRenameTool.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Editor.h"

static const FName MPRenameToolTabName("MPRenameTool");

#define LOCTEXT_NAMESPACE "FMPRenameTool"

// Singleton instance
TSharedPtr<FMPRenameTool> FMPRenameTool::Singleton = nullptr;

TSharedPtr<FMPRenameTool> FMPRenameTool::Get() {
    if (!Singleton.IsValid()) {
        Singleton = MakeShareable(new FMPRenameTool());
    }
    return Singleton;
}

bool FMPRenameTool::IsAvailable() {
    return Singleton.IsValid();
}

void FMPRenameTool::StartupModule() {
    // Ensure the singleton instance is used
    TSharedPtr<FMPRenameTool> SingletonInstance = FMPRenameTool::Get();

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MPRenameToolTabName, FOnSpawnTab::CreateRaw(SingletonInstance.Get(), &FMPRenameTool::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("FMPRenameToolTabTitle", "MP RenameTool"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

    SingletonInstance->RenameToolWidget = SNew(MPRenameToolWidget);
    SingletonInstance->RenameToolBL = MakeShareable(new MPRenameToolBL());
    SingletonInstance->RegisterMenus();
}

void FMPRenameTool::ShutdownModule() {
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MPRenameToolTabName);
    RenameToolWidget.Reset();
    RenameToolBL.Reset();
    Singleton.Reset();
}

void FMPRenameTool::RegisterMenus() {
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
    MenuExtender->AddMenuBarExtension("Help", EExtensionHook::After, nullptr, FMenuBarExtensionDelegate::CreateRaw(this, &FMPRenameTool::AddMenuExtension));

    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FMPRenameTool::AddMenuExtension(FMenuBarBuilder& Builder) {
    Builder.AddPullDownMenu(
        LOCTEXT("MPToolsMenu", "MP Tools"),
        LOCTEXT("MPToolsMenu_Tooltip", "Open MP Tools menu"),
        FNewMenuDelegate::CreateRaw(this, &FMPRenameTool::FillMenu)
    );
}

void FMPRenameTool::FillMenu(FMenuBuilder& MenuBuilder) {
    MenuBuilder.AddMenuEntry(
        LOCTEXT("MPRenameToolMenuEntry", "Rename Tool"),
        LOCTEXT("MPRenameToolMenuEntryTooltip", "Open the MP Rename Tool"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FMPRenameTool::PluginButtonClicked))
    );
}

void FMPRenameTool::PluginButtonClicked() {
    FGlobalTabmanager::Get()->TryInvokeTab(MPRenameToolTabName);
}

TSharedRef<SDockTab> FMPRenameTool::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs) {
    if (RenameToolWidget.IsValid()) {
        return RenameToolWidget->SpawnTab();
    }
    else {
        return SNew(SDockTab).TabRole(ETabRole::NomadTab)
            [
                SNew(STextBlock)
                    .Text(LOCTEXT("ErrorText", "Rename Tool Widget is not valid"))
            ];
    }
}

bool FMPRenameTool::RenameSelectedActors(const FString& NewBaseName) const {
    if (RenameToolBL.IsValid()) {
        return RenameToolBL->RenameSelectedActors(NewBaseName);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("Rename Tool logic is not valid"));
        return false;
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMPRenameTool, MPRenameTool)
