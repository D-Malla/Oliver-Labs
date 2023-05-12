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

	/* HUD */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
		UDoorButtonWidget* DoorHUD;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UDoorButtonWidget> DoorHUDClass;

	UFUNCTION()
	void DisplayButtonDoorHUD(bool IsLocked);
	UFUNCTION()
	void RemoveButtonDoorHUD();
	
};
