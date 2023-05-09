// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/Doors/Door.h"
#include "ButtonDoor.generated.h"

UCLASS()
class OLIVER_LABS_API AButtonDoor : public ADoor
{
	GENERATED_BODY()

public:

	AButtonDoor();

	virtual void BeginPlay() override;

	void OpenDoor() override;
	void CloseDoor() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* ButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UBoxComponent* ButtonVolume;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Properties")
		bool bIsDoorLocked;

	// Delegate Callbacks
	UFUNCTION()
		void OnButtonVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnButtonVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	// GETTERS
	FORCEINLINE bool GetIsDoorLocked() { return bIsDoorLocked; }

	// SETTERS
	FORCEINLINE void SetIsDoorLocked(bool DoorLocked) { bIsDoorLocked = DoorLocked; }
	
};
