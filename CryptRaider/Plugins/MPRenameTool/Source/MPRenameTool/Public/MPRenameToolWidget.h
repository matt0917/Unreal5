//******************************************************************************
// File:        MPRenameWidget
// Author:      Joonseo.Park
// Date:        5/16/2024/Thu 1:47:22 AM
// Description: 
//******************************************************************************

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"

class MPRenameToolWidget : public SCompoundWidget {
public:
    SLATE_BEGIN_ARGS(MPRenameToolWidget)
        : _TabSize(FVector2D(300.f, 150.f))
        , _Separator("_") {} // Default value for Separator
        SLATE_ARGUMENT(FVector2D, TabSize)
        SLATE_ARGUMENT(FString, Separator) // Allow Separator to be set during widget instantiation
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    TSharedRef<SDockTab> SpawnTab();

private:
    TSharedPtr<SEditableTextBox> RenameInputTextBox;
    TSharedPtr<SEditableTextBox> OldTextBox;
    TSharedPtr<SEditableTextBox> NewTextBox;
    TSharedPtr<SEditableTextBox> PrefixTextBox;
    TSharedPtr<SEditableTextBox> SuffixTextBox;
    TSharedPtr<SEditableTextBox> SeparatorTextBox;
    FString Separator;
    FVector2D TabSize;

    bool OnSeperatorTextChanged(const FText& InText, FText& OutErrorText) const;
    FReply OnAddPrefixAndSuffixButtonClicked();
    FReply OnRenameButtonClicked();
    FReply OnReplaceButtonClicked();
};
