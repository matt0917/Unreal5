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

bool MPRenameToolBL::AddPrefixAndSuffixToActors(const FString& PrefixText, const FString& SuffixText, const FString& separator) const {
    // Access the editor selection
    TObjectPtr<USelection> SelectedActors = GEditor->GetSelectedActors();
    if (SelectedActors && SelectedActors->Num() > 0) {
        // Declare undo scope
        FScopedTransaction Transaction(LOCTEXT("AddPrefixSuffixToActorsTransaction", "Add Prefix/Suffix to Actors"));

        int32 Index = 1;
        int32 TotalSelectedActors = SelectedActors->Num();

        for (FSelectionIterator It(*SelectedActors); It; ++It) {
            if (TObjectPtr<AActor> Actor = Cast<AActor>(*It)) {
                FString BaseNameWithSuffix = InsertBeforeNumericSuffix(Actor->GetActorLabel(), SuffixText, separator);
                const FString NewName = FString::Printf(TEXT("%s%s"), *PrefixText, *BaseNameWithSuffix);
                Actor->Modify(); // Mark the actor as modified for undo
                Actor->SetActorLabel(NewName, true);
                Index++;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool MPRenameToolBL::RenameSelectedActors(const FString& NewBaseName, const FString& PrefixText, const FString& SuffixText) const {
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
                const FString NewName = FString::Printf(TEXT("%s%s%s%0*d"), *PrefixText, *NewBaseName, *SuffixText, PaddingDigits, Index);
                Actor->Modify(); // Mark the actor as modified for undo
                Actor->SetActorLabel(NewName, true);
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
    if (SelectedActors && SelectedActors->Num() > 0 && !OldText.IsEmpty()) {
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
                    Actor->SetActorLabel(NewName, true);

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

FString MPRenameToolBL::RemoveTrailingNumbers(const FString& Input) const{
    FString Result = Input;
    // Find the last non-numeric character from the end of the string
    int32 LastNonNumeric = -1;
    for (int32 i = Input.Len() - 1; i >= 0; --i) {
        if (!FChar::IsDigit(Input[i])) {
            LastNonNumeric = i;
            break;
        }
    }
    // If found, cut the string up to this character
    return LastNonNumeric != -1 ? Result.Left(LastNonNumeric + 1) : Result;
}

FString MPRenameToolBL::InsertBeforeNumericSuffix(const FString& Original, const FString& InputToInsert, const FString& Separator) const {
    FString Result = Original;
    int32 FirstNumeric = -1;

    // Find the position of the first numeric character from the end of the string
    for (int32 i = Result.Len() - 1; i >= 0; --i) {
        if (!FChar::IsDigit(Result[i])) {
            FirstNumeric = i+1;
            break;
        }
    }

    // If we found a numeric sequence
    if (FirstNumeric != -1 && FirstNumeric < Result.Len()) {
        // Check the separator is empty
        if (!Separator.IsEmpty()){        
            if (FirstNumeric >= Separator.Len() && Result.Mid(FirstNumeric - Separator.Len(), Separator.Len()) == Separator) {
                // Insert the new string at the position of the separator
                Result.InsertAt(FirstNumeric - Separator.Len(), InputToInsert);
            }
            else {
                // If not the same, insert the string at the found position
                Result.InsertAt(FirstNumeric, InputToInsert);
            }
        }
        else {
             Result.InsertAt(FirstNumeric, InputToInsert);
        }
    }

    return Result;
}



#undef LOCTEXT_NAMESPACE
