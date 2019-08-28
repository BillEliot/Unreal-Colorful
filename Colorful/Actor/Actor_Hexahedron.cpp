// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Hexahedron.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Actor/Actor_Obstacle.h"
#include "ColorfulGameModeBase.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AActor_Hexahedron::AActor_Hexahedron()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> object_Hexahedron(TEXT("StaticMesh'/Game/Mesh/Model/SM_Hexahedron.SM_Hexahedron'"));
	pHexahedron = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hexahedron"));
	RootComponent = pHexahedron;
	if (object_Hexahedron.Succeeded()) pHexahedron->SetStaticMesh(object_Hexahedron.Object);

	pBox_0 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_0"));
	pBox_0->SetupAttachment(RootComponent);
	pBox_0->SetBoxExtent(FVector(185.f, 1.f, 27.f));
	pBox_0->SetRelativeLocationAndRotation(FVector(161.f, -279.f, 26.7), FQuat(FRotator(0, 30.f, 0)));
	pBox_0->OnComponentBeginOverlap.AddDynamic(this, &AActor_Hexahedron::OnBeginOverlap_Box_0);

	pBox_1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_1"));
	pBox_1->SetupAttachment(RootComponent);
	pBox_1->SetBoxExtent(FVector(185.f, 1.f, 27.f));
	pBox_1->SetRelativeLocationAndRotation(FVector(321.9, -0.2, 26.7), FQuat(FRotator(0, 90.f, 0)));
	pBox_1->OnComponentBeginOverlap.AddDynamic(this, &AActor_Hexahedron::OnBeginOverlap_Box_1);

	pBox_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_2"));
	pBox_2->SetupAttachment(RootComponent);
	pBox_2->SetBoxExtent(FVector(185.f, 1.f, 27.f));
	pBox_2->SetRelativeLocationAndRotation(FVector(160.9, 278.8, 26.7), FQuat(FRotator(0, 150.f, 0)));
	pBox_2->OnComponentBeginOverlap.AddDynamic(this, &AActor_Hexahedron::OnBeginOverlap_Box_2);

	pBox_3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_3"));
	pBox_3->SetupAttachment(RootComponent);
	pBox_3->SetBoxExtent(FVector(185.f, 1.f, 27.f));
	pBox_3->SetRelativeLocationAndRotation(FVector(-160.1, 278.7, 26.7), FQuat(FRotator(0, 30.f, 0)));
	pBox_3->OnComponentBeginOverlap.AddDynamic(this, &AActor_Hexahedron::OnBeginOverlap_Box_3);

	pBox_4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_4"));
	pBox_4->SetupAttachment(RootComponent);
	pBox_4->SetBoxExtent(FVector(185.f, 1.f, 27.f));
	pBox_4->SetRelativeLocationAndRotation(FVector(-321.9, -0.2, 26.7), FQuat(FRotator(0, 90.f, 0)));
	pBox_4->OnComponentBeginOverlap.AddDynamic(this, &AActor_Hexahedron::OnBeginOverlap_Box_4);

	pBox_5 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_5"));
	pBox_5->SetupAttachment(RootComponent);
	pBox_5->SetBoxExtent(FVector(185.f, 1.f, 27.f));
	pBox_5->SetRelativeLocationAndRotation(FVector(-160.9, -278.8, 26.7), FQuat(FRotator(0, 150.f, 0)));
	pBox_5->OnComponentBeginOverlap.AddDynamic(this, &AActor_Hexahedron::OnBeginOverlap_Box_5);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> object_CurveFloat(TEXT("CurveFloat'/Game/Curve.Curve'"));
	if (object_CurveFloat.Succeeded()) pCurveFloat = object_CurveFloat.Object;
}

// Called when the game starts or when spawned
void AActor_Hexahedron::BeginPlay()
{
	Super::BeginPlay();

	pTimeline = new FTimeline();
	OnTimelineFloat.BindUFunction(this, TEXT("TimelineFun"));
	pTimeline->AddInterpFloat(pCurveFloat, OnTimelineFloat);
}

// Called every frame
void AActor_Hexahedron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (pTimeline->IsPlaying()) pTimeline->TickTimeline(DeltaTime);
}

void AActor_Hexahedron::RotateLeft() {
	if (!pTimeline->IsPlaying()) {
		CurrentRotation = pHexahedron->GetComponentRotation();
		PurposeRotation = CurrentRotation - FRotator(0, 60.f, 0);
		pTimeline->PlayFromStart();
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->SetIsForzen(true);
	}
}
void AActor_Hexahedron::RotateRight() {
	if (!pTimeline->IsPlaying()) {
		CurrentRotation = pHexahedron->GetComponentRotation();
		PurposeRotation = CurrentRotation + FRotator(0, 60.f, 0);
		pTimeline->PlayFromStart();
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->SetIsForzen(true);
	}
}

void AActor_Hexahedron::TimelineFun(const float value) {
	FRotator rotation = FMath::LerpRange<float>(CurrentRotation, PurposeRotation, value);
	pHexahedron->SetWorldRotation(FQuat(rotation));

	if (value == 1.f) Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->SetIsForzen(false);
}

FAttachmentTransformRules rules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
void AActor_Hexahedron::OnBeginOverlap_Box_0(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AActor_Obstacle>(OtherActor)->Destroy();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(0);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pHexahedron, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(0, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(0);
	}
}
void AActor_Hexahedron::OnBeginOverlap_Box_1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(1);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pHexahedron, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(1, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(1);
	}
}
void AActor_Hexahedron::OnBeginOverlap_Box_2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AActor_Obstacle>(OtherActor)->Destroy();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(2);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pHexahedron, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(2, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(2);
	}
}
void AActor_Hexahedron::OnBeginOverlap_Box_3(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AActor_Obstacle>(OtherActor)->Destroy();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(3);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pHexahedron, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(3, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(3);
	}
}
void AActor_Hexahedron::OnBeginOverlap_Box_4(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AActor_Obstacle>(OtherActor)->Destroy();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(4);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pHexahedron, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(4, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(4);
	}
}
void AActor_Hexahedron::OnBeginOverlap_Box_5(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AActor_Obstacle>(OtherActor)) {
		if (Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->GetIsForzen()) {
			Cast<AActor_Obstacle>(OtherActor)->Destroy();
			return;
		}

		Cast<AActor_Obstacle>(OtherActor)->SetColumn(5);
		Cast<AActor_Obstacle>(OtherActor)->StopMove();
		Cast<AActor_Obstacle>(OtherActor)->AttachToComponent(pHexahedron, rules);
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateObstacleInfo(5, Cast<AActor_Obstacle>(OtherActor));
		Cast<AColorfulGameModeBase>(GetWorld()->GetAuthGameMode())->Check(5);
	}
}
