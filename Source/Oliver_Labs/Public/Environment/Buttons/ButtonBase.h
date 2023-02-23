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

	void ButtonPressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* ButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* ButtonCollision;

	/* Button Functionality */
	// Delegates ** MUST ** have UFUNCTION
	UFUNCTION()
	void OnButtonVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnButtonVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditInstanceOnly, Category = "Door Link")
	ADoorBase* DoorREF;
private:
// Door References
	//UPROPERTY(EditDefaultsOnly, Category = "Door Link")
	//TSubclassOf<ADoorBase> DoorBP;

	UPROPERTY(EditInstanceOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	uint8 ButtonID;

	bool bIsButtonPressed;

public:
// GETTERS
	FORCEINLINE uint8 GetButtonID() { return ButtonID; }
	FORCEINLINE bool GetIsButtonPressed() { return bIsButtonPressed; }

// SETTERS
	FORCEINLINE void SetIsButtonPressed(bool bPressedButton) { bIsButtonPressed = bPressedButton; }
	
};
