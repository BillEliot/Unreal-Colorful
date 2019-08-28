// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Obstacle.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Actor/Actor_Obstacle.h"
#include "ColorfulGameModeBase.h"
#include "Engine/World.h"

// Sets default values
AActor_Obstacle::AActor_Obstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanMove = true;
	bTag = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> object_Obstacle(TEXT("StaticMesh'/Game/Mesh/Model/SM_Obstacle.SM_Obstacle'"));
	pObstacle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle"));
	RootComponent = pObstacle;
	if (object_Obstacle.Succeeded()) pObstacle->SetStaticMesh(object_Obstacle.Object);

	pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	pBox->SetupAttachment(RootComponent);
	pBox->SetBoxExtent(FVector(185.f, 1.f, 26.f));
	pBox->SetRelativeLocationAndRotation(FVector(5.7f, -16.f, -0.2f), FQuat(FRotator(0, 0, 0)));
	pBox->OnComponentBeginOverlap.AddDynamic(this, &AActor_Obstacle::OnBeginOverlap);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> object_Material_Red(TEXT("Material'/Game/Mesh/Material/M_Red.M_Red'"));
	if (object_Material_Red.Succeeded()) pMaterial_Red = object_Material_Red.Object;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> object_Material_Green(TEXT("MaterialInstanceConstant'/Game/Mesh/Material/M_Green.M_Green'"));
	if (object_Material_Green.Succeeded()) pMaterial_Green = object_Material_Green.Object;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> object_Material_Blue(TEXT("MaterialInstanceConstant'/Game/Mesh/Material/M_Blue.M_Blue'"));
	if (object_Material_Blue.Succeeded()) pMaterial_Blue = object_Material_Blue.Object;
}

// Called when the game starts or when spawned
void AActor_Obstacle::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetActorLocation();

	int32 nIndex = FMath::RandRange(0, 2);
	switch (nIndex) {
	case 0:
		pObstacle->SetMaterial(0, pMaterial_Red);
		nColorCode = 0;
		break;
	case 1:
		pObstacle->SetMaterial(0, pMaterial_Green);
		nColorCode = 1;
		break;
	case 2:
		pObstacle->SetMaterial(0, pMaterial_Blue);
		nColorCode = 2;
		break;
	}
}

// Called every frame
void AActor_Obstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanMove) {
		float delta = 100.f * DeltaTime;
		if (CurrentLocation.X != 0) {
			if (CurrentLocation.X > 0) CurrentLocation.X -= delta;
			else CurrentLocation.X += delta;
		}
		if (CurrentLocation.Y != 0) {
			if (CurrentLocation.Y > 0) CurrentLocation.Y -= delta * 1.8;
			else CurrentLocation.Y += delta * 1.8;
		}
		SetActorLocation(CurrentLocation);
	}
}

void AActor_Obstacle::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != this && Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AActor_Obstacle>(OtherActor)->Destroy();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(nColumn);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		FAttachmentTransformRules rules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pObstacle, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(nColumn, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(nColumn);
	}
}
