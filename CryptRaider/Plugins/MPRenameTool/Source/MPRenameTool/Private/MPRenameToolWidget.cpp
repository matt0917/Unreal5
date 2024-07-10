//******************************************************************************
// File:        MPRenameWidget
// Author:      Joonseo.Park
// Date:        5/16/2024/Thu 1:47:22 AM
// Description: 
//******************************************************************************

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
    Separator = InArgs._Separator;

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
                            .HAlign(HAlign_Left)
                            .AutoWidth()
                            [
                                SNew(SRichTextBlock)
                                    .Text(LOCTEXT("PrefixLabel", "Prefix: "))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            .FillWidth(0.4f)
                            [
                                SAssignNew(PrefixTextBox, SEditableTextBox)
                            ]
                            + SHorizontalBox::Slot()
                            .VAlign(VAlign_Center)
                            .HAlign(HAlign_Left)
                            .AutoWidth()
                            [
                                SNew(SRichTextBlock)
                                    .Text(LOCTEXT("SuffixLabel", "Suffix: "))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            .FillWidth(0.4f)
                            [
                                SAssignNew(SuffixTextBox, SEditableTextBox)
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            .FillWidth(0.1f)
                            [
                                SAssignNew(SeparatorTextBox, SEditableTextBox)
                                .Text(LOCTEXT("UnderScoreChar", "_"))
                                .ToolTipText(FText::FromString(TEXT("Separator of the prefix and the suffix of the name of the Actor(s)")))
                                .OnVerifyTextChanged(this, &MPRenameToolWidget::OnSeperatorTextChanged)
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            .FillWidth(0.2f)
                            [
                                SNew(SButton)
                                    .Text(LOCTEXT("LeftArrow", "\u21D0"))
                                    .ButtonColorAndOpacity(FSlateColor(FLinearColor(FLinearColor(0.043f, 0.608f, 0.98f, 1.f))))
                                    .HAlign(HAlign_Center)
                                    .VAlign(VAlign_Center)
                                    .ToolTipText(FText::FromString(TEXT("Concatenate the prefix and suffix with the current name of the Actor(s)")))
                                    .OnClicked(this, &MPRenameToolWidget::OnAddPrefixAndSuffixButtonClicked)
                            ]
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
                                .Text(LOCTEXT("NewnameLabel", "New name: "))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            [
                                SAssignNew(RenameInputTextBox, SEditableTextBox)
                                    .HintText(LOCTEXT("NewnameHintText", "Enter New Name:"))
                            ]
                    ]
                    + SVerticalBox::Slot()
                    .Padding(2)
                    [
                        SNew(SButton)
                            .Text(LOCTEXT("ButtonText", "Rename Actor(s)"))
                            .HAlign(HAlign_Center)
                            .VAlign(VAlign_Center)
                            .ToolTipText(FText::FromString(TEXT("Rename the Actor(s) currently selected. Do nothing with empty.")))
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
                                    .Text(LOCTEXT("Label", "Replace: "))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            [
                                SAssignNew(OldTextBox, SEditableTextBox)
                                    .HintText(LOCTEXT("ReplaceHintText", "Enter text to replace:"))
                            ]
                            + SHorizontalBox::Slot()
                            .VAlign(VAlign_Center)
                            .AutoWidth()
                            [
                                SNew(SRichTextBlock)
                                    .Text(LOCTEXT("Label", "To: "))
                            ]
                            + SHorizontalBox::Slot()
                            .HAlign(HAlign_Fill)
                            [
                                SAssignNew(NewTextBox, SEditableTextBox)
                                    .HintText(LOCTEXT("ReplaceWithHintText", "Enter text to replace with:"))
                            ]
                    ]
                    + SVerticalBox::Slot()
                    .Padding(5)
                    [
                        SNew(SButton)
                        .Text(LOCTEXT("ReplaceButtonText", "Replace Text"))
                        .HAlign(HAlign_Center)
                        .VAlign(VAlign_Center)
                        .ToolTipText(FText::FromString(TEXT("Replace the text found in the name of the Actor(s) currently selected.")))
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

bool MPRenameToolWidget::OnSeperatorTextChanged(const FText& InText, FText& OutErrorText) const {
    if (InText.ToString().Len() > 1) {
        OutErrorText = LOCTEXT("SeparatorError", "Separator must be a single character.");
        return false;
    }

    return true;
}

FReply MPRenameToolWidget::OnAddPrefixAndSuffixButtonClicked(){
    FString _Separator = FString("");
    const FText& _text = SeparatorTextBox->GetText();
    if (!_text.IsEmpty()){
        _Separator = _text.ToString(); // Set _Separator to an empty FString instead
    }
    // Get and trim the suffix text
    FString SuffixText = SuffixTextBox->GetText().ToString().TrimStartAndEnd();
    FString PrefixText = PrefixTextBox->GetText().ToString().TrimStartAndEnd();
    if (!PrefixText.IsEmpty()) {
        PrefixText.Append(_Separator);
    }
    if (!SuffixText.IsEmpty()) {
        SuffixText.InsertAt(0, _Separator);
    }
    FMPRenameTool::Get()->AddPrefixAndSuffixToActors(PrefixText, SuffixText, _Separator);
    return FReply::Handled();
}

FReply MPRenameToolWidget::OnRenameButtonClicked() {
    FString NewBaseName = RenameInputTextBox->GetText().ToString().TrimStartAndEnd();
    FString PrefixText = PrefixTextBox->GetText().ToString().TrimStartAndEnd();
    if (!PrefixText.IsEmpty()) {
        PrefixText.Append(Separator);
    }
    FString SuffixText = SuffixTextBox->GetText().ToString().TrimStartAndEnd();
    if (!SuffixText.IsEmpty()) {
        SuffixText.InsertAt(0, Separator);
    }
    FMPRenameTool::Get()->RenameSelectedActors(NewBaseName, PrefixText, SuffixText);  // Updated to use TSharedPtr
    return FReply::Handled();
}

FReply MPRenameToolWidget::OnReplaceButtonClicked() {
    FString OldText = OldTextBox->GetText().ToString();
    FString NewText = NewTextBox->GetText().ToString();
    FMPRenameTool::Get()->ReplaceTextForSelectedActors(OldText, NewText);
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
