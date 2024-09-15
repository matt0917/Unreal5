// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM(BlueprintType) // Exposes this enum to the editor in Blueprints
enum class EWeaponType : uint8 
{
	Light     UMETA(DisplayName = "Light Weapon"),
	Medium    UMETA(DisplayName = "Medium Weapon"),
	Heavy     UMETA(DisplayName = "Heavy Weapon")
};



UCLASS(Abstract)
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PullTrigger();

	virtual void RunVfx() PURE_VIRTUAL(ABaseWeapon::PullTrigger, );
	virtual void RunSfx() PURE_VIRTUAL(ABaseWeapon::PullTrigger, );

protected:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	class UParticleSystem* MuzzleFlashFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
	class USoundBase* MuzzeleFlashSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	float MaxRange;

public:
	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta = (DisplayPriority = 1))
	EWeaponType WeaponType;

};
