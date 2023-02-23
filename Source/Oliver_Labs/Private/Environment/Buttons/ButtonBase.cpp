// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Characters/Oliver.h"
#include "Environment/Buttons/ButtonBase.h"
#include "Environment/Doors/DoorBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AButtonBase::AButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ButtonComponent"));
	ButtonComponent->SetupAttachment(GetRootComponent());

	ButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonCollision"));
	ButtonCollision->SetupAttachment(ButtonComponent);
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();

	ButtonCollision->OnComponentBeginOverlap.AddDynamic(this, &AButtonBase::OnButtonVolumeBeginOverlap);
	ButtonCollision->OnComponentEndOverlap.AddDynamic(this, &AButtonBase::OnButtonVolumeEndOverlap);
}

void AButtonBase::OnButtonVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AButtonBase::OnButtonVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Orange, FString::Printf(TEXT("IsButtonPressed: %s"), GetIsButtonPressed() ? TEXT("True") : TEXT("False")));
	}
}

void AButtonBase::ButtonPressed()
{
	if (DoorREF && ButtonID == DoorREF->GetDoorID())
	{
		if (bIsButtonPressed)
		{
			DoorREF->OpenDoor();
		}
	}
}

