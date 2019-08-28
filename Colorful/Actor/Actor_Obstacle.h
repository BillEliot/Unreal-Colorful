// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Obstacle.generated.h"

UCLASS()
class COLORFUL_API AActor_Obstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActor_Obstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	class UStaticMeshComponent* pObstacle;
	class UBoxComponent* pBox;

	FVector CurrentLocation;
	bool bCanMove;
	bool bTag;
	int32 nColumn;
	int32 nColorCode;

	class UMaterialInterface* pMaterial_Red;
	class UMaterialInterface* pMaterial_Green;
	class UMaterialInterface* pMaterial_Blue;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FORCEINLINE void StopMove() { bCanMove = false; }
	FORCEINLINE int32 GetColorCode() const { return nColorCode; }
	FORCEINLINE void SetColumn(int32 ColumnIndex) { nColumn = ColumnIndex; }
	FORCEINLINE void SetTag(bool tag) { bTag = tag; }
	FORCEINLINE bool GetTag() const { return bTag; }
};
