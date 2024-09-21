// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ShooterCharacter.generated.h"


class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class AGun;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogShooterCharacter, Log, All);



UCLASS(config=Game)
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Gun", meta = (DisplayPriority = 1))
	TArray< TSubclassOf<AGun> > GunClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchWeaponLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchWeaponRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;


	TArray<AGun*> SpawnedGuns;

	void SwitchLeft();
	void SwitchRight();
	void SwitchWeapon(int32 Direction);
	void Shoot();

protected:
	UPROPERTY()
	AGun* Gun;

	bool bDead;

public:
	UPROPERTY(EditAnywhere, Category="Gun", meta = (DisplayPriority = 1))
	int32 WeaponIndex;

	UPROPERTY(EditAnywhere, Category = "Health")
	float DamageRatio;

	UFUNCTION()
	virtual void HandleDestruction();

	//Make callable in bluerprint and make this pure function
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDead() const;

private:
	void DestroyAllGuns();

	struct FTimerHandle GunDestroyTimerHandle;
};
