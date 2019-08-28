// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorfulGameModeBase.h"
#include "Pawn/Pawn_Camera.h"
#include "Actor/Actor_Obstacle.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TimerManager.h"


AColorfulGameModeBase::AColorfulGameModeBase() {
	DefaultPawnClass = APawn_Camera::StaticClass();
	Array_Obstacles.AddZeroed(6);
	IsFrozen = false;

	Array_InitTransform.Add(FTransform(FQuat(FRotator(0, 30.f, 0)), FVector(360.f, -655, 30.f)));
	Array_InitTransform.Add(FTransform(FQuat(FRotator(0, 90.f, 0)), FVector(750.f, 0, 30.f)));
	Array_InitTransform.Add(FTransform(FQuat(FRotator(0, -210.f, 0)), FVector(370.f, 640.f, 30.f)));
	Array_InitTransform.Add(FTransform(FQuat(FRotator(0, -150.f, 0)), FVector(-360.f, 655, 30.f)));
	Array_InitTransform.Add(FTransform(FQuat(FRotator(0, -90.f, 0)), FVector(-750.f, 0, 30.f)));
	Array_InitTransform.Add(FTransform(FQuat(FRotator(0, -30.f, 0)), FVector(-370.f, -640, 30.f)));
}

void AColorfulGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AColorfulGameModeBase::TimerFun, 3.f, true);
}

void AColorfulGameModeBase::TimerFun() {
	int32 nIndex = FMath::RandRange(0, 5);

	GetWorld()->SpawnActor<AActor_Obstacle>(AActor_Obstacle::StaticClass(), Array_InitTransform[nIndex]);
}

void AColorfulGameModeBase::UpdateObstacleInfo(const int32 nColumnIndex, AActor_Obstacle* pObstacle) {
	Array_Obstacles[nColumnIndex].Add(pObstacle);
}

void AColorfulGameModeBase::Check(const int32 nCurrentColumn) {
	int32 nRow = Array_Obstacles[nCurrentColumn].Num() - 1;
	int32 nCount = 1;

	Array_Obstacles[nCurrentColumn][nRow]->SetTag(true);
	int32 nColorCode = Array_Obstacles[nCurrentColumn][nRow]->GetColorCode();
	// Right
	for (int32 nColumn = nCurrentColumn + 1; nColumn <= 5; nColumn++) {
		if (Array_Obstacles[nColumn].IsValidIndex(nRow) && Array_Obstacles[nColumn][nRow]->GetColorCode() == nColorCode) {
			Array_Obstacles[nColumn][nRow]->SetTag(true);
			nCount++;
		}
		else break;
	}
	// Left
	for (int32 nColumn = nCurrentColumn - 1; nColumn >= -5; nColumn--) {
		// Map
		int32 nMapColumn = 0;
		if (nColumn < 0) nMapColumn = nColumn + 6;
		else nMapColumn = nColumn;

		if (Array_Obstacles[nMapColumn].IsValidIndex(nRow) && Array_Obstacles[nMapColumn][nRow]->GetColorCode() == nColorCode) {
			Array_Obstacles[nMapColumn][nRow]->SetTag(true);
			nCount++;
		}
		else break;
	}

	// Destroy
	if (nCount >= 3) {
		for (int32 nColumn = 0; nColumn <= 5; nColumn++) {
			if (Array_Obstacles[nColumn].IsValidIndex(nRow) && Array_Obstacles[nColumn][nRow]->GetTag()) {
				// Update the next obstacle's location
				FVector Location;
				if (Array_Obstacles[nColumn].IsValidIndex(nRow + 1)) Location = Array_Obstacles[nColumn][nRow]->GetActorLocation();
				else Location = FVector(0,0,0);
				Array_Obstacles[nColumn][nRow]->Destroy();
				Array_Obstacles[nColumn].RemoveAt(nRow);

				if (Location != FVector(0,0,0)) Array_Obstacles[nColumn][nRow + 1]->SetActorLocation(Location);
			}
		}
	}
	else {
		for (int32 nColumn = 0; nColumn <= 5; nColumn++) {
			if (Array_Obstacles[nColumn].IsValidIndex(nRow)) Array_Obstacles[nColumn][nRow]->SetTag(false);
		}
	}
}
