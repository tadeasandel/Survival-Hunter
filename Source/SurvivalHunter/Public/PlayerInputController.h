// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/Delegate.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputController.generated.h"

class UInputComponent;

DECLARE_MULTICAST_DELEGATE(FMouseLeftReleased);
DECLARE_MULTICAST_DELEGATE(FMouseLeftPressed);
DECLARE_MULTICAST_DELEGATE(FMouseRightReleased);
DECLARE_MULTICAST_DELEGATE(FMouseRightPressed);
DECLARE_MULTICAST_DELEGATE(FJumpPressed);
DECLARE_MULTICAST_DELEGATE(FJumpReleased);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALHUNTER_API UPlayerInputController : public UActorComponent
{
	GENERATED_BODY()

public:
	//// Sets default values for this component's properties
	UPlayerInputController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	UInputComponent* InputComponent;

	float XMouseValue;
	float YMouseValue;

	float XKeyboardValue;
	float YKeyboardValue;

	bool MouseleftHeld;
	bool MouseRightHeld;

	FMouseLeftReleased OnMouseLeftReleased;
	FMouseLeftPressed OnMouseLeftPressed;

	FMouseRightReleased OnMouseRightReleased;
	FMouseRightPressed OnMouseRightPressed;

	FJumpPressed OnJumpPressed;
	FJumpReleased OnJumpReleased;

private:
	void HandleMouseXAxis(float Value);
	void HandleMouseYAxis(float Value);
	void HandleKeyboardXAxis(float Value);
	void HandleKeyboardYAxis(float Value);

	void OnMouseLeftUp();
	void OnMouseLeftDown();
	void OnMouseRightUp();
	void OnMouseRightDown();
	void OnJumpUp();
	void OnJumpDown();
};
