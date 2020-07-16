// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraControllerComponent.generated.h"

class UCameraComponent;
class AActor;
class UStaticMeshComponent;
class UPlayerInputController;
class UChildActorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALHUNTER_API UCameraControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(Transient)
		UPlayerInputController* InputController;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> CameraActorToSpawn;

	UPROPERTY(VisibleAnywhere)
	AActor* CameraHolder;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UChildActorComponent* CameraSubObject;

	UPROPERTY(EditAnywhere)
		float MouseSensitivity;

	UPROPERTY(EditAnywhere)
		float MaxCameraDistance;

	float RotationY;
	float RotationX;

	float CameraDistance;

	void SpawnCamera();
	void TurnCamera();
	void ScrollCamera();
};
