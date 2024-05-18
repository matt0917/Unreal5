#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "MPRenameToolWidget.h"
#include "MPRenameToolBL.h"

class FMPRenameTool : public IModuleInterface {
public:
    static TSharedPtr<FMPRenameTool> Get();
    static bool IsAvailable();

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    void PluginButtonClicked();
    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
    bool RenameSelectedActors(const FString& NewName) const;

private:
    void RegisterMenus();
    void AddMenuExtension(FMenuBarBuilder& Builder);
    void FillMenu(FMenuBuilder& MenuBuilder);

    TSharedPtr<class FUICommandList> PluginCommands;
    TSharedPtr<MPRenameToolWidget> RenameToolWidget;
    TSharedPtr<MPRenameToolBL> RenameToolBL;
    static TSharedPtr<FMPRenameTool> Singleton;
};
