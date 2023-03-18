// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/Buttons/ButtonBase.h"

#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Characters/Oliver.h"
#include "Environment/Doors/DoorBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AButtonBase::AButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ButtonComponent"));
	ButtonComponent->SetupAttachment(GetRootComponent());

	ButtonVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonVolume"));
	ButtonVolume->SetupAttachment(ButtonComponent);

	bIsButtonPressed = false;
	bIsSpawningObject = false;
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AButtonBase::ButtonPressed()
{
	if (DoorREF && ButtonID == DoorREF->GetDoorID() && bIsButtonPressed)
	{
		DoorREF->SetIsDoorUnlocked(true);
	}
}

