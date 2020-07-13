// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputController.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Delegates/Delegate.h"

UPlayerInputController::UPlayerInputController()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerInputController::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &UPlayerInputController::HandleKeyboardYAxis);
		InputComponent->BindAxis("MoveRight", this, &UPlayerInputController::HandleKeyboardXAxis);
		InputComponent->BindAxis("MouseForward", this, &UPlayerInputController::HandleMouseYAxis);
		InputComponent->BindAxis("MourseRight", this, &UPlayerInputController::HandleMouseXAxis);

		InputComponent->BindAction("M1", IE_Pressed, this, &UPlayerInputController::OnMouseLeftDown);
		InputComponent->BindAction("M1", IE_Released, this, &UPlayerInputController::OnMouseLeftUp);
		InputComponent->BindAction("M2", IE_Pressed, this, &UPlayerInputController::OnMouseLeftDown);
		InputComponent->BindAction("M2", IE_Released, this, &UPlayerInputController::OnMouseLeftUp);
		InputComponent->BindAction("Jump", IE_Pressed, this, &UPlayerInputController::OnJumpDown);
		InputComponent->BindAction("Jump", IE_Released, this, &UPlayerInputController::OnJumpUp);
	}
}

void UPlayerInputController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInputController::HandleMouseYAxis(float Value)
{
	XMouseValue = Value;
}

void UPlayerInputController::HandleMouseXAxis(float Value)
{
	YMouseValue = Value;
}

void UPlayerInputController::HandleKeyboardYAxis(float Value)
{
	XKeyboardValue = Value;
}

void UPlayerInputController::HandleKeyboardXAxis(float Value)
{
	YKeyboardValue = Value;
}

void UPlayerInputController::OnMouseLeftUp()
{
	OnMouseLeftReleased.Broadcast();
}

void UPlayerInputController::OnMouseLeftDown()
{
	OnMouseLeftPressed.Broadcast();
}

void UPlayerInputController::OnMouseRightUp()
{
	OnMouseRightReleased.Broadcast();
}

void UPlayerInputController::OnMouseRightDown()
{
	OnMouseRightPressed.Broadcast();
}

void UPlayerInputController::OnJumpUp()
{
	OnJumpReleased.Broadcast();
}

void UPlayerInputController::OnJumpDown()
{
	OnJumpPressed.Broadcast();
}