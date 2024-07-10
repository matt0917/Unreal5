//******************************************************************************
// File:        MPRenameToolBL
// Author:      Joonseo.Park
// Date:        5/17/2024/Fri 3:07:36 AM
// Description: 
//******************************************************************************

#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"


class MPRenameToolBL: public TSharedFromThis<MPRenameToolBL>
{
public:
    bool AddPrefixAndSuffixToActors(const FString& PrefixText, const FString& SuffixText, const FString& separator) const;
    bool RenameSelectedActors(const FString& NewBaseName, const FString& PrefixText, const FString& SuffixText) const;
    bool ReplaceTextForSelectedActors(const FString& OldText, const FString& NewText) const;

private:
    FString RemoveTrailingNumbers(const FString& Input) const;
    FString InsertBeforeNumericSuffix(const FString& Original, const FString& InputToInsert, const FString& Separator) const;
};

