// Fill out your copyright notice in the Description page of Project Settings.


#include "SQuickStartWindowMenu.h"
#include "SlateOptMacros.h"

DEFINE_LOG_CATEGORY(logTemp);
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SQuickStartWindowMenu::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
        SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Top)
                    [
                        SNew(STextBlock)
                            .Text(FText::FromString("Test Button"))
                    ]
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Top)
                    [
                        SNew(SButton)
                        .Text(FText::FromString("Press Me"))
                        .OnClicked(this, &SQuickStartWindowMenu::OnTestButtonClicked)
                    ]
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Top)
                    [
                        SNew(STextBlock)
                            .Text(FText::FromString("Test Checkbox"))
                    ]
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Top)
                    [
                        SNew(SCheckBox)
                        .OnCheckStateChanged(this, &SQuickStartWindowMenu::OnTestCheckboxStateChanged)
                        .IsChecked(this, &SQuickStartWindowMenu::IsTestBoxChecked)
                    ]
            ]
	];
	
}


FReply SQuickStartWindowMenu::OnTestButtonClicked()
{
    UE_LOG(logTemp, Warning, TEXT("Hello, world! The checkbox is %s."), (bIsTestBoxChecked ? TEXT("checked") : TEXT("unchecked")));

    return FReply::Handled();
}

void SQuickStartWindowMenu::OnTestCheckboxStateChanged(ECheckBoxState NewState)
{
    bIsTestBoxChecked = NewState == ECheckBoxState::Checked ? true : false;
}

ECheckBoxState SQuickStartWindowMenu::IsTestBoxChecked() const
{
    return bIsTestBoxChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
