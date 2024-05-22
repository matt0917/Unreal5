#include "MPRenameToolWidget.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "ToolMenus.h"
#include "Editor.h"
#include "Engine/Selection.h"
#include "GameFramework/Actor.h"
#include "MPRenameTool.h"

#define LOCTEXT_NAMESPACE "MPRenameToolWidget"

void MPRenameToolWidget::Construct(const FArguments& InArgs) {
    TabSize = InArgs._TabSize;

    ChildSlot
        [
            SNew(SBox)
            .MinDesiredWidth(TabSize.X)
            .MinDesiredHeight(TabSize.Y)
            [
                SNew(SVerticalBox)
                    + SVerticalBox::Slot()
                    .Padding(2)
                    [
                        SNew(SHorizontalBox)
                            + SHorizontalBox::Slot()
                            .VAlign(VAlign_Center)
                            .AutoWidth()
                            [
                                SNew(SRichTextBlock)
                                .Text(LOCTEXT("Label", "New name:"))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            [
                                SAssignNew(RenameInputTextBox, SEditableTextBox)
                                    .HintText(LOCTEXT("HintText", "Enter New Name:"))
                            ]
                    ]
                    + SVerticalBox::Slot()
                    .Padding(5)
                    [
                        SNew(SButton)
                            .Text(LOCTEXT("ButtonText", "Rename Actor(s)"))
                            .HAlign(HAlign_Center)
                            .VAlign(VAlign_Center)
                            .OnClicked(this, &MPRenameToolWidget::OnRenameButtonClicked)
                    ]
                    + SVerticalBox::Slot()
                    .Padding(2)
                    [
                        SNew(SHorizontalBox)
                            + SHorizontalBox::Slot()
                            .VAlign(VAlign_Center)
                            .AutoWidth()
                            [
                                SNew(SRichTextBlock)
                                    .Text(LOCTEXT("Label", "Replace:"))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            [
                                SAssignNew(OldTextBox, SEditableTextBox)
                                    .HintText(LOCTEXT("HintText", "Enter text to replace:"))
                            ]
                            + SHorizontalBox::Slot()
                            .VAlign(VAlign_Center)
                            .AutoWidth()
                            [
                                SNew(SRichTextBlock)
                                    .Text(LOCTEXT("Label", "To:"))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            [
                                SAssignNew(NewTextBox, SEditableTextBox)
                                    .HintText(LOCTEXT("HintText", "Enter text to replace with:"))
                            ]
                    ]
                    + SVerticalBox::Slot()
                    .Padding(5)
                    [
                        SNew(SButton)
                        .Text(LOCTEXT("ButtonText", "Replace Text"))
                        .HAlign(HAlign_Center)
                        .VAlign(VAlign_Center)
                        .OnClicked(this, &MPRenameToolWidget::OnReplaceButtonClicked)
                    ]
            ]
        ];
}

TSharedRef<SDockTab> MPRenameToolWidget::SpawnTab() {
    TSharedRef<SDockTab> DockTab =
        SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        .OnTabClosed(SDockTab::FOnTabClosedCallback::CreateLambda([this](TSharedRef<SDockTab> ClosedTab) {
         TabSize = ClosedTab->GetContent()->GetDesiredSize();
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

FReply MPRenameToolWidget::OnReplaceButtonClicked() {
    FString OldText = OldTextBox->GetText().ToString();
    FString NewText = NewTextBox->GetText().ToString();
    FMPRenameTool::Get()->ReplaceTextForSelectedActors(OldText, NewText);  
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
