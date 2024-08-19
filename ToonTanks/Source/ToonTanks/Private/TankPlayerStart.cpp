// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerStart.h"
#include "Components/CapsuleComponent.h"


ATankPlayerStart::ATankPlayerStart(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer), CapsuleHeight(64.f), CapsuleWidth(64.f)
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp){
		CapsuleComp->SetCapsuleSize(CapsuleWidth, CapsuleHeight);
	}
}
