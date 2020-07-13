// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "PlayerInputController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateSignatureImpl.inl"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InputController = GetOwner()->FindComponentByClass<UPlayerInputController>();
	StaticMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	if (InputController)
	{
		InputController->OnJumpPressed.AddUObject(this, &UPlayerMovementComponent::Jump);
	}
}


// Called every frame
void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (InputController)
	{
		StaticMesh->AddForce(FVector(InputController->XKeyboardValue, InputController->YKeyboardValue, StaticMesh->ComponentVelocity.Z) * DeltaTime * MovementSpeed);
	}
}

void UPlayerMovementComponent::Jump()
{
	StaticMesh->AddForce(FVector(StaticMesh->ComponentVelocity.X, StaticMesh->ComponentVelocity.Y, JumpForce));
}


