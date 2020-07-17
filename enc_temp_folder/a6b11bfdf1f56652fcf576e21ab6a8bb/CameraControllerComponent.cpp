// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControllerComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Math/TransformNonVectorized.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerInputController.h"
#include "Engine/EngineTypes.h"
#include "Components/ChildActorComponent.h"

// Sets default values for this component's properties
UCameraControllerComponent::UCameraControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	InputController = GetOwner()->FindComponentByClass<UPlayerInputController>();

	SpawnCamera();
}

// Called every frame
void UCameraControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CameraHolder && InputController && StaticMesh)
	{
		FVector PlayerLocation = StaticMesh->GetComponentTransform().GetLocation() + FVector(0.0f, 0.5f, 0.0f);
		CameraHolder->SetActorLocation(PlayerLocation);
		TurnCamera();
		ScrollCamera();
	}
}

void UCameraControllerComponent::SpawnCamera()
{
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FVector SpawnPosition = GetOwner()->GetTransform().GetLocation() + FVector(0.0f, 0.5f, 0.0f);
	FActorSpawnParameters SpawnParams;
	CameraHolder = GetWorld()->SpawnActor(CameraActorToSpawn, &SpawnPosition, &SpawnRotation, SpawnParams);
	TArray<AActor*> Children;
	CameraHolder->GetAllChildActors(Children);

	CameraSubObject = Children[0];
	UE_LOG(LogTemp, Warning, TEXT("%s"), (*CameraSubObject->GetName()));
}

void UCameraControllerComponent::TurnCamera()
{
	RotationX += InputController->XMouseValue * MouseSensitivity;
	RotationY += InputController->YMouseValue * MouseSensitivity;

	RotationY = FMath::Clamp(RotationY, -90.0f, 90.0f);

	FRotator NewCameraRotation = FRotator(RotationY, RotationX, 0);

	CameraHolder->SetActorRotation(NewCameraRotation);
}

void UCameraControllerComponent::ScrollCamera()
{
	CameraDistance += InputController->MouseScrollValue;

	FHitResult HitResult;

	FVector PlayerPosition = StaticMesh->GetComponentLocation();
	FVector CameraPosition = CameraSubObject->GetTransform().GetLocation();

	FVector CameraEndPosition = (CameraPosition - PlayerPosition);
	CameraEndPosition.Normalize();
	CameraEndPosition *= MaxCameraDistance;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerPosition, CameraEndPosition, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	if (HitResult.GetActor())
	{
		CameraDistance = HitResult.Distance - 5.0f;
		UE_LOG(LogTemp,Warning, TEXT("Hitting actor named %s"), (*HitResult.GetActor()->GetName()))
	}

	CameraDistance = FMath::Clamp(CameraDistance, 0.0f, MaxCameraDistance);

	UE_LOG(LogTemp, Error, TEXT("Camera distance is %f"), CameraDistance);

	FVector CurrentCameraPosition = CameraSubObject->GetActorLocation();
	CurrentCameraPosition.X = -CameraDistance;

	CameraSubObject->GetTransform().SetLocation(CurrentCameraPosition);
}