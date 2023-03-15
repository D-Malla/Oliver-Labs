// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OliverPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OLIVER_LABS_API AOliverPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOliverPlayerController();
	virtual void BeginPlay() override;
	
};
