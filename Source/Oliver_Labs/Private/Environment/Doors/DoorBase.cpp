// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Doors/DoorBase.h"

// Sets default values
ADoorBase::ADoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorComponent"));
	DoorComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ADoorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorBase::OpenDoor()
{
	if (DoorOpenAnim)
	{
		DoorComponent->PlayAnimation(DoorOpenAnim, false);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoorBase::CloseDoor, 5.f, false);
	}
}

void ADoorBase::CloseDoor()
{
	if (DoorCloseAnim)
	{
		DoorComponent->PlayAnimation(DoorCloseAnim, false);
	}
}

