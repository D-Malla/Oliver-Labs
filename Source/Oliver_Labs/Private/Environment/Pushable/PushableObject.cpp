// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Pushable/PushableObject.h"

// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void APushableObject::BeginPlay()
{
	Super::BeginPlay();

}

void APushableObject::Interact()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString(TEXT("Interacted with pushable object!")));
	}
}
