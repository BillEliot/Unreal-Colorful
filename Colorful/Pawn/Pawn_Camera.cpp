// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn_Camera.h"
#include "Camera/CameraComponent.h"
#include "Public/EngineUtils.h"
#include "Actor/Actor_Hexahedron.h"
#include "Components/InputComponent.h"


// Sets default values
APawn_Camera::APawn_Camera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	pCamera->SetupAttachment(RootComponent);
	pCamera->AddLocalRotation(FQuat(FRotator(-90.f, 0, 0)));
}

// Called when the game starts or when spawned
void APawn_Camera::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0, 0, 1500.f));
	SetActorRotation(FQuat(FRotator(0, 0, 0)));

	// Get Actor_Hexahedron in the world
	for (TActorIterator<AActor_Hexahedron> iterator(GetWorld()); iterator; ++iterator) {
		pHexahedron = *iterator;
	}
}

// Called every frame
void APawn_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawn_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RotateLeft", EInputEvent::IE_Pressed, this, &APawn_Camera::RotateLeft);
	PlayerInputComponent->BindAction("RotateRight", EInputEvent::IE_Pressed, this, &APawn_Camera::RotateRight);
}

void APawn_Camera::RotateLeft() {
	if (pHexahedron) pHexahedron->RotateLeft();
}

void APawn_Camera::RotateRight() {
	if (pHexahedron) pHexahedron->RotateRight();
}
