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
        : _TabSize(FVector2D(300.f, 150.f)) {}
        SLATE_ARGUMENT(FVector2D, TabSize)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    TSharedRef<SDockTab> SpawnTab();

private:
    TSharedPtr<SEditableTextBox> RenameInputTextBox;
    TSharedPtr<SEditableTextBox> OldTextBox;
    TSharedPtr<SEditableTextBox> NewTextBox;
    FVector2D TabSize;

    FReply OnRenameButtonClicked();
    FReply OnReplaceButtonClicked();
};
