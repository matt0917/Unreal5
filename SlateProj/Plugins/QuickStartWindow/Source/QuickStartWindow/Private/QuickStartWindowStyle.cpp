// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuickStartWindowStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FQuickStartWindowStyle::StyleInstance = nullptr;

void FQuickStartWindowStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FQuickStartWindowStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FQuickStartWindowStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("QuickStartWindowStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FQuickStartWindowStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("QuickStartWindowStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("QuickStartWindow")->GetBaseDir() / TEXT("Resources"));

	Style->Set("QuickStartWindow.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FQuickStartWindowStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FQuickStartWindowStyle::Get()
{
	return *StyleInstance;
}
