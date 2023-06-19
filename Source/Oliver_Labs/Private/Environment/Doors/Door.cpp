// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Doors/Door.h"

#include "Characters/Oliver.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorComponent"));
	RootComponent = DoorComponent;

	DoorVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorVolume"));
	DoorVolume->SetupAttachment(DoorComponent);

	OpenDoorAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("OpenDoorAudioComponent"));
	OpenDoorAudioComponent->SetupAttachment(DoorComponent);
	OpenDoorAudioComponent->bAutoActivate = false;
	CloseDoorAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CloseDoorAudioComponent"));
	CloseDoorAudioComponent->SetupAttachment(DoorComponent);
	CloseDoorAudioComponent->bAutoActivate = false;

	Oliver = nullptr;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	// Binding Overlap callbacks for Door Volume
	DoorVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnDoorVolumeBeginOverlap);
	DoorVolume->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnDoorVolumeEndOverlap);
}

void ADoor::OnDoorVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		OpenDoor();
}

void ADoor::OnDoorVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		CloseDoor();
}

void ADoor::OpenDoor()
{
	if (DoorOpenAnim)
	{
		DoorComponent->PlayAnimation(DoorOpenAnim, false);

		//FTimerHandle TimerHandle;
		//GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoor::CloseDoor, DoorTimer, false);
	}

	if (OpenDoorAudioComponent->Sound) // Check if a sound is set within audio component
	{
		OpenDoorAudioComponent->Play(0.1f);
	}
}

void ADoor::CloseDoor()
{
	if (DoorCloseAnim)
	{
		DoorComponent->PlayAnimation(DoorCloseAnim, false);
	}

	if (CloseDoorAudioComponent->Sound)  // Check if a sound is set within audio component
	{
		CloseDoorAudioComponent->Play();
	}
}