// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Oliver.generated.h"

class AButtonBase;
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

	AButtonBase* Button;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
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

	// Input Variables
	bool bIsCrouched;
	bool bCanPressButton;

	// Input Callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void ToggleCrouch();
	void ButtonPress();

	// Overlap Delegates
	// Delegates ** MUST ** have UFUNCTION
	UFUNCTION()
	void OnButtonVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnButtonVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
/* GETTERS */
	FORCEINLINE bool GetIsCrouched() { return bIsCrouched; }

/* SETTERS */
};
