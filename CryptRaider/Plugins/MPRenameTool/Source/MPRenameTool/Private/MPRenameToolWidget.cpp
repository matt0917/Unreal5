#include "MPRenameToolWidget.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "ToolMenus.h"
#include "Editor.h"
#include "Engine/Selection.h"
#include "GameFramework/Actor.h"
#include "MPRenameTool.h"

#define LOCTEXT_NAMESPACE "MPRenameToolWidget"

void MPRenameToolWidget::Construct(const FArguments& InArgs) {
    Width = InArgs._Width;
    Height = InArgs._Height;

    ChildSlot
        [
            SNew(SBox)
                .WidthOverride(Width)
                .HeightOverride(Height)
                [
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot()
                        .Padding(5)
                        [
                            SAssignNew(RenameInputTextBox, SEditableTextBox)
                                .HintText(LOCTEXT("HintText", "Enter New Name:"))
                        ]
                        + SVerticalBox::Slot()
                        .Padding(5)
                        [
                            SNew(SButton)
                                .Text(LOCTEXT("ButtonText", "Rename"))
                                .HAlign(HAlign_Center)
                                .VAlign(VAlign_Center)
                                .OnClicked(this, &MPRenameToolWidget::OnRenameButtonClicked)
                        ]
                ]
        ];
}

TSharedRef<SDockTab> MPRenameToolWidget::SpawnTab() {
    TSharedRef<SDockTab> DockTab =
        SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        .OnTabClosed(SDockTab::FOnTabClosedCallback::CreateLambda([this](TSharedRef<SDockTab> ClosedTab) {
        FVector2D Size = ClosedTab->GetContent()->GetDesiredSize();
        Width = Size.X;
        Height = Size.Y;
            }))
        .Content()
                [
                    AsShared() // Use this widget as the content of the tab
                ];

            return DockTab;
}

FReply MPRenameToolWidget::OnRenameButtonClicked() {
    FString NewBaseName = RenameInputTextBox->GetText().ToString();
    FMPRenameTool::Get()->RenameSelectedActors(NewBaseName);  // Updated to use TSharedPtr
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
