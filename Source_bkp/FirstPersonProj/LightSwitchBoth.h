// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitchBoth.generated.h"

UCLASS()
class FIRSTPERSONPROJ_API ALightSwitchBoth : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch Components")
	class UPointLightComponent* PointLight1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch Components")
	class USphereComponent* Sphere1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch Variables")
	float DesiredIntensity;

	// Sets default values for this actor's properties
	ALightSwitchBoth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 무언가 구체 컴포넌트에 들어설 때 호출 */
	UFUNCTION(BlueprintNativeEvent, Category="Switch Functions")
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/// <summary>
	/// LightSwitchBoth 의 소스 파일에서 생성자는 그대로입니다. 하지만 OnOverlapBegin 및 OnOverlapEnd 함수에는 변경이 필요합니다. 이 함수는 이제 BlueprintNativeEvent 입니다. 즉 이 클래스에서 파생되는 블루프린트에서는, OnOverlapBegin 및 OnOverlapEnd 함수를 덮어쓰는 이벤트 배치가 가능하며, 함수가 정상적으로 호출될 때 실행된다는 뜻입니다. 그 이벤트 중 하나가 존재하지 않으면, 그 함수의 C++ 구현이 대신 실행됩니다.
	/// </summary>
	void OnOverlapBegin_Implementation(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** 무언가 구체 컴포넌트에서 나올때 호출*/
	UFUNCTION(BlueprintNativeEvent, Category="Switch Component")
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/// <summary>
	/// LightSwitchBoth 의 소스 파일에서 생성자는 그대로입니다. 하지만 OnOverlapBegin 및 OnOverlapEnd 함수에는 변경이 필요합니다. 이 함수는 이제 BlueprintNativeEvent 입니다. 즉 이 클래스에서 파생되는 블루프린트에서는, OnOverlapBegin 및 OnOverlapEnd 함수를 덮어쓰는 이벤트 배치가 가능하며, 함수가 정상적으로 호출될 때 실행된다는 뜻입니다. 그 이벤트 중 하나가 존재하지 않으면, 그 함수의 C++ 구현이 대신 실행됩니다.
	/// </summary>
	void OnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Toggle light function
	UFUNCTION(BlueprintCallable, Category="Switch Component")
	void ToggleLight();
};
