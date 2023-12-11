// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_LOG_CATEGORY_EXTERN(logTemp, Log, All);
/**
 * 
 */
class QUICKSTARTWINDOW_API SQuickStartWindowMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQuickStartWindowMenu)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnTestButtonClicked();
	void OnTestCheckboxStateChanged(ECheckBoxState);
	ECheckBoxState IsTestBoxChecked() const;

protected:
	bool bIsTestBoxChecked;
};
