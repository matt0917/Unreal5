//******************************************************************************
// File:        MPRenameToolBL
// Author:      Joonseo.Park
// Date:        5/17/2024/Fri 3:07:05 AM
// Description: 
//******************************************************************************

#include "MPRenameToolBL.h"
#include "Editor.h"
#include "Engine/Selection.h"
#include "GameFramework/Actor.h"

#define LOCTEXT_NAMESPACE "MPRenameToolBL"

bool MPRenameToolBL::RenameSelectedActors(const FString& NewBaseName) const {
    // Access the editor selection
    TObjectPtr<USelection> SelectedActors = GEditor->GetSelectedActors();
    if (SelectedActors && SelectedActors->Num() > 0 && !NewBaseName.IsEmpty()) {
        // Declare undo scope
        FScopedTransaction Transaction(LOCTEXT("RenameActorsTransaction", "Rename Actors"));

        int32 Index = 1;
        int32 TotalSelectedActors = SelectedActors->Num();
        int32 PaddingDigits = FMath::CeilToInt(FMath::LogX(10.0f, static_cast<float>(TotalSelectedActors + 1)));

        for (FSelectionIterator It(*SelectedActors); It; ++It) {
            if (TObjectPtr<AActor> Actor = Cast<AActor>(*It)) {
                const FString NewName = FString::Printf(TEXT("%s%0*d"), *NewBaseName, PaddingDigits, Index);
                Actor->Modify(); // Mark the actor as modified for undo
                Actor->SetActorLabel(NewName);
                Index++;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool MPRenameToolBL::ReplaceTextForSelectedActors(const FString& OldText, const FString& NewText) const {
    // Access the editor selection
    TObjectPtr<USelection> SelectedActors = GEditor->GetSelectedActors();
    if (SelectedActors && SelectedActors->Num() > 0 && !OldText.IsEmpty() && !NewText.IsEmpty()) {
        // Declare undo scope
        FScopedTransaction Transaction(LOCTEXT("ReplaceActorsTextTransaction", "Replace text of Actors"));

        int32 ReplacedCount = 0;

        for (FSelectionIterator It(*SelectedActors); It; ++It) {
            if (TObjectPtr<AActor> Actor = Cast<AActor>(*It)) {
                // Get current actor name
                FString CurrentName = Actor->GetActorLabel();

                // Check if the current name contains the old text
                if (CurrentName.Contains(OldText)) {
                    // Replace old text with new text
                    FString NewName = CurrentName.Replace(*OldText, *NewText);

                    // Mark the actor as modified for undo
                    Actor->Modify();
                    Actor->SetActorLabel(NewName);

                    // Increment replaced count
                    ReplacedCount++;
                }
            }
        }
        return ReplacedCount > 0; // Return true if any names were replaced
    }
    else {
        return false;
    }
}

#undef LOCTEXT_NAMESPACE
