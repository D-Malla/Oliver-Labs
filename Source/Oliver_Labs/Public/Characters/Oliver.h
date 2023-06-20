// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Oliver.generated.h"

class AOliverPlayerController;
class AButtonDoor;
class AButtonVolume;
class APushableObject;

class UBoxComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

UCLASS()
class OLIVER_LABS_API AOliver : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOliver();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Object References */
	UPROPERTY()
	AButtonDoor* ButtonDoor;
	UPROPERTY()
	UBoxComponent* ButtonVolume;
	UPROPERTY()
	APushableObject* PushableObject;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		AOliverPlayerController* OliverPlayerController;

/* Animation References */
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* ButtonPressAnimMontage;

/* Core Components */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComponent;

/* Input */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputMappingContext* OliverMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* MovementAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* CrouchAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* ButtonPressAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		UInputAction* InteractAction;

	// Input Variables
	bool bIsCrouched;
	bool bCanPressButton;
	bool bCanPushObject;

	// Input Callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void ToggleCrouch();
	void PressButton();
	void InteractWithObject();

public:
/* GETTERS */
	FORCEINLINE AOliverPlayerController* GetOliverPlayerController() const { return OliverPlayerController; }
	FORCEINLINE bool GetIsCrouched() const { return bIsCrouched; }
	FORCEINLINE bool GetCanPressButton() const { return bCanPressButton; }

/* SETTERS */
	FORCEINLINE void SetCanPressButton(bool CanPress) { bCanPressButton = CanPress; }

};
