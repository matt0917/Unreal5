// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

void AEnemyCharacter::HandleDestruction() 
{
	Super::HandleDestruction();
	SetLifeSpan(5.f);
}