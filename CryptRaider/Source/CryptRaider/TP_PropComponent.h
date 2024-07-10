// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TP_PropComponent.generated.h"


class ACryptRaiderCharacter;

/**
 * Class Prop can be possessed
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTP_PropComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTP_PropComponent();

	/** Prop offset from character's location*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector PropOffset;

	/** Attaches the actor to a character */
	UFUNCTION(BlueprintCallable, Category = "Prop")
	bool AttachProp(ACryptRaiderCharacter* TargetCharacter);

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this prop*/
	ACryptRaiderCharacter* Character;
};
