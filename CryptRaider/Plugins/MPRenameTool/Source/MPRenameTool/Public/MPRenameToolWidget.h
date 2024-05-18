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
        : _Width(300), _Height(100) {}
        SLATE_ARGUMENT(uint32, Width)
        SLATE_ARGUMENT(uint32, Height)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    TSharedRef<SDockTab> SpawnTab();

private:
    TSharedPtr<SEditableTextBox> RenameInputTextBox;
    uint32 Width;
    uint32 Height;

    FReply OnRenameButtonClicked();
};
