// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"

class ADoorBase;
class UBoxComponent;

UCLASS()
class OLIVER_LABS_API AButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category = "Door Link")
	ADoorBase* DoorREF;
	
	void ButtonPressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* ButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* ButtonVolume;
private:

	UPROPERTY(EditInstanceOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	uint8 ButtonID;

	UPROPERTY()
	bool bIsButtonPressed;

	UPROPERTY(EditInstanceOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	bool bIsSpawningObject;

	UPROPERTY(EditInstanceOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ObjectToSpawn;

public:
// GETTERS
	FORCEINLINE uint8 GetButtonID() { return ButtonID; }
	FORCEINLINE bool GetIsButtonPressed() { return bIsButtonPressed; }

// SETTERS
	FORCEINLINE void SetIsButtonPressed(bool bPressedButton) { bIsButtonPressed = bPressedButton; }
	
};
