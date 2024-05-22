#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "MPRenameToolWidget.h"
#include "MPRenameToolBL.h"

class FMPRenameTool : public IModuleInterface {
public:
    static TSharedPtr<FMPRenameTool> Get();

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    void PluginButtonClicked();
    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
    bool RenameSelectedActors(const FString& NewName) const;
    bool ReplaceTextForSelectedActors(const FString& OldText, const FString& NewText) const;

private:
    void RegisterMenus();
    void AddMenuExtension(FMenuBarBuilder& Builder);
    void FillMenu(FMenuBuilder& MenuBuilder);

    TSharedPtr<class FUICommandList> PluginCommands;
    TSharedPtr<class MPRenameToolWidget, ESPMode::ThreadSafe> RenameToolWidget;
    TSharedPtr<class MPRenameToolBL> RenameToolBL;
    static TSharedPtr<FMPRenameTool> Singleton;
};
