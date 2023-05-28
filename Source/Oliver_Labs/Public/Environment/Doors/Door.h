// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class AOliver;
class UBoxComponent;
class USoundCue;

UCLASS()
class OLIVER_LABS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	virtual void OpenDoor();
	virtual void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Core Properties */
	AOliver* Oliver;

	//UPROPERTY(EditInstanceOnly, Category = "Properties")
	//float DoorTimer;

		// Overlap Delegate Callbacks
	UFUNCTION()
		void OnDoorVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnDoorVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* DoorComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UBoxComponent* DoorVolume;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USoundCue* OpenSFX;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USoundCue* CloseSFX;
	UPROPERTY(EditInstanceOnly, Category = "Animations")
		UAnimSequence* DoorOpenAnim;
	UPROPERTY(EditInstanceOnly, Category = "Animations")
		UAnimSequence* DoorCloseAnim;

public:
	// Getters
	// Setters
};
