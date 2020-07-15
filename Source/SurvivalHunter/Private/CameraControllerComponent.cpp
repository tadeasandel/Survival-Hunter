// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControllerComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Math/TransformNonVectorized.h"
#include "Components/StaticMeshComponent.h"

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
	if (StaticMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("WELL WE DID IT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UNREAL SUCKS"));			
	}
	SpawnCamera();
}


// Called every frame
void UCameraControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CameraHolder)
	{
		if (StaticMesh)
		{
			FVector PlayerLocation = StaticMesh->GetComponentTransform().GetLocation() + FVector(0.0f, 0.5f, 0.0f);
			CameraHolder->SetActorLocation(PlayerLocation);
			UE_LOG(LogTemp, Warning, TEXT("%s vs location %s"), (*CameraHolder->GetTransform().GetLocation().ToString()),(*PlayerLocation.ToString()));
		}
	}
}

void UCameraControllerComponent::SpawnCamera()
{
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FVector SpawnPosition = GetOwner()->GetTransform().GetLocation() + FVector(0.0f,0.5f,0.0f);
	FActorSpawnParameters SpawnParams;
	CameraHolder = GetWorld()->SpawnActor(CameraActorToSpawn, &SpawnPosition, &SpawnRotation, SpawnParams);
}

