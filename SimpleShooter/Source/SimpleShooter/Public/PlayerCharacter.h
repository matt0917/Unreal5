// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API APlayerCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	virtual void HandleDestruction() override;

};
