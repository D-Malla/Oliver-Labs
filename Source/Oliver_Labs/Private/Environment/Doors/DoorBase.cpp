// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Doors/DoorBase.h"
#include "Characters/Oliver.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorBase::ADoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorComponent"));
	DoorComponent->SetupAttachment(GetRootComponent());

	DoorVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorVolume"));
	DoorVolume->SetupAttachment(DoorComponent);

	//DoorTimer = 0.f;
	bIsDoorUnlocked = false;
}

// Called when the game starts or when spawned
void ADoorBase::BeginPlay()
{
	Super::BeginPlay();

	if (bUsingButton)
	{
		bIsDoorUnlocked = false;
	}
	else
	{
		bIsDoorUnlocked = true;
	}

	//Binding Overlap callbacks for Door Volume
	DoorVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoorBase::OnDoorVolumeBeginOverlap);
	DoorVolume->OnComponentEndOverlap.AddDynamic(this, &ADoorBase::OnDoorVolumeEndOverlap);


}

void ADoorBase::OnDoorVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsDoorUnlocked)
	{
		OpenDoor();
	}
}

void ADoorBase::OnDoorVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsDoorUnlocked)
	{
		CloseDoor();
	}
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

		//FTimerHandle TimerHandle;
		//GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoorBase::CloseDoor, DoorTimer, false);
	}
}

void ADoorBase::CloseDoor()
{
	if (DoorCloseAnim)
	{
		DoorComponent->PlayAnimation(DoorCloseAnim, false);
	}
}

