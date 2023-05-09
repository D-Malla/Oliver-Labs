// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OliverPlayerController.generated.h"

class UDoorButtonWidget;
class UTextBlock;

UCLASS()
class OLIVER_LABS_API AOliverPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOliverPlayerController();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDoorButtonWidget> DoorHUDClass;
	UPROPERTY(EditAnywhere, Category = "HUD")
		UDoorButtonWidget* DoorHUD;

	UFUNCTION()
	void DisplayButtonDoorHUD(bool IsLocked);
	UFUNCTION()
	void RemoveButtonDoorHUD();
	
};
