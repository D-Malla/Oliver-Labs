// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorBase.generated.h"

class UBoxComponent;

UCLASS()
class OLIVER_LABS_API ADoorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Core Properties */
	//UPROPERTY(EditInstanceOnly, Category = "Properties")
	//float DoorTimer;

	UPROPERTY(EditInstanceOnly, Category = "Properties")
	bool bUsingButton;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* DoorComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* DoorVolume;

	UPROPERTY(EditInstanceOnly, Category = "Animations")
	UAnimSequence* DoorOpenAnim;

	UPROPERTY(EditInstanceOnly, Category = "Animations")
	UAnimSequence* DoorCloseAnim;

	UPROPERTY(EditInstanceOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	uint8 DoorID;

	UPROPERTY(VisibleInstanceOnly, Category = "Properties")
	bool bIsDoorUnlocked;

	UFUNCTION()
	void OnDoorVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnDoorVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// GETTERS
	FORCEINLINE uint8 GetDoorID() { return DoorID; }
	FORCEINLINE bool GetIsDoorUnlocked() { return bIsDoorUnlocked; }

	// SETTERS
	FORCEINLINE void SetIsDoorUnlocked(bool bDoorUnlocked) { bIsDoorUnlocked = bDoorUnlocked; }

};
