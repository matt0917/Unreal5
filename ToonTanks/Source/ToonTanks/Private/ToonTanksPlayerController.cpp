// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled) 
{
	// Set mouse cursor visible while the tank is alive
	if (bPlayerEnabled){
		GetPawn()->EnableInput(this);
	} else {
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}
