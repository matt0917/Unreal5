// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Mover.h"
#include "OverlapTriggerBoxComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UOverlapTriggerBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UOverlapTriggerBoxComponent();
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	FName AcceptableTag;

	UMover* Mover;

public:
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetAcceptableActor() const;

protected:
	virtual void BeginPlay() override;
};
