// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ColorfulGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class COLORFUL_API AColorfulGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AColorfulGameModeBase();

protected:
	virtual void BeginPlay() override;

	TArray<FTransform> Array_InitTransform;
	TArray<TArray<class AActor_Obstacle*>> Array_Obstacles;

	FTimerHandle TimerHandle;
	void TimerFun();

	bool IsFrozen;

public:
	void UpdateObstacleInfo(const int32 nColumnIndex, class AActor_Obstacle* pObstacle);
	void Check(const int32 nCurrentColumn);
	FORCEINLINE void SetIsForzen(bool frozen) { IsFrozen = frozen; }
	FORCEINLINE bool GetIsForzen() const { return IsFrozen; }
};
