// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OliverPlayerController.h"

#include "Components/TextBlock.h"
#include "HUD/DoorButtonWidget.h"

AOliverPlayerController::AOliverPlayerController()
{
	// HUD
	DoorHUD = nullptr;
	DoorHUDClass = nullptr;
}

void AOliverPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AOliverPlayerController::DisplayButtonDoorHUD(bool IsLocked)
{
	DoorHUD = CreateWidget<UDoorButtonWidget>(this, DoorHUDClass);
	
	if (IsLocked)
	{
		DoorHUD->UnlockTextBlock->SetText(FText::FromString("Press E to Interact!"));
	}
	else
	{
		DoorHUD->UnlockTextBlock->SetText(FText::FromString("Door is already Unlocked!"));
	}
		DoorHUD->AddToPlayerScreen();
}

void AOliverPlayerController::RemoveButtonDoorHUD()
{
	DoorHUD->RemoveFromParent();
}

