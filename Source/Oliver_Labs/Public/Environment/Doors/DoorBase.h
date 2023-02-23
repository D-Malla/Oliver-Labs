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
	UPROPERTY(EditInstanceOnly, Category = "Properties")
	bool bUsingButton;

	UPROPERTY(EditInstanceOnly, Category = "Properties")
	bool bUsingVolume;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* DoorComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimSequence* DoorOpenAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimSequence* DoorCloseAnim;

	UPROPERTY(EditInstanceOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	uint8 DoorID;

	UPROPERTY()
	ADoorBase* DoorREF;

public:
	// GETTERS
	FORCEINLINE uint8 GetDoorID() { return DoorID; }

	// SETTERS
	FORCEINLINE void SetDoorREF(ADoorBase* Door) { DoorREF = Door; }
};
