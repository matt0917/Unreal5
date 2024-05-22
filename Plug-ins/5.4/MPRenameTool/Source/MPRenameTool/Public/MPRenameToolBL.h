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
    bool RenameSelectedActors(const FString& NewBaseName) const;
    bool ReplaceTextForSelectedActors(const FString& OldText, const FString& NewText) const;
};
