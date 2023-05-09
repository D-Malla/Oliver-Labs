// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Doors/ButtonDoor.h"

#include "Characters/Oliver.h"
#include "Characters/OliverPlayerController.h"
#include "Components/BoxComponent.h"
#include "Environment/Doors/ButtonDoor.h"

AButtonDoor::AButtonDoor()
{
	ButtonComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ButtonComponent"));
	ButtonComponent->SetupAttachment(GetRootComponent());

	ButtonVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonVolume"));
	ButtonVolume->SetupAttachment(ButtonComponent);

	bIsDoorLocked = true;
}

void AButtonDoor::BeginPlay()
{
	Super::BeginPlay();

	//Binding Overlap callbacks for Button Volume
	ButtonVolume->OnComponentBeginOverlap.AddDynamic(this, &AButtonDoor::OnButtonVolumeBeginOverlap);
	ButtonVolume->OnComponentEndOverlap.AddDynamic(this, &AButtonDoor::OnButtonVolumeEndOverlap);
}

void AButtonDoor::OpenDoor()
{
	if (!bIsDoorLocked)
	{
		Super::OpenDoor();
	}
}

void AButtonDoor::CloseDoor()
{
	if (!bIsDoorLocked)
	{
		Super::CloseDoor();
	}
}

void AButtonDoor::OnButtonVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Oliver = Cast<AOliver>(OtherActor);
	Oliver->ButtonDoor = this;
	Oliver->ButtonVolume = this->ButtonVolume;

	if (Oliver && bIsDoorLocked)
	{
		Oliver->SetCanPressButton(true);
		Oliver->GetOliverPlayerController()->DisplayButtonDoorHUD(true);
	}
	else
	{
		Oliver->SetCanPressButton(false);
		Oliver->GetOliverPlayerController()->DisplayButtonDoorHUD(false);
	}
}

void AButtonDoor::OnButtonVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Oliver->SetCanPressButton(false);
	Oliver->GetOliverPlayerController()->RemoveButtonDoorHUD();

	Oliver->ButtonDoor = nullptr;
	Oliver->ButtonVolume = nullptr;
	Oliver = nullptr;
}
