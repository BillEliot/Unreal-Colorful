// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Actor_Hexahedron.generated.h"

UCLASS()
class COLORFUL_API AActor_Hexahedron : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_Hexahedron();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	class UStaticMeshComponent* pHexahedron;
	class UBoxComponent* pBox_0;
	class UBoxComponent* pBox_1;
	class UBoxComponent* pBox_2;
	class UBoxComponent* pBox_3;
	class UBoxComponent* pBox_4;
	class UBoxComponent* pBox_5;

	class UCurveFloat* pCurveFloat;
	FTimeline* pTimeline;
	FOnTimelineFloat OnTimelineFloat;
	UFUNCTION()
		void TimelineFun(const float value);

	FRotator CurrentRotation;
	FRotator PurposeRotation;

	UFUNCTION()
		void OnBeginOverlap_Box_0(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBeginOverlap_Box_1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBeginOverlap_Box_2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBeginOverlap_Box_3(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBeginOverlap_Box_4(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBeginOverlap_Box_5(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void RotateLeft();
	void RotateRight();
};
