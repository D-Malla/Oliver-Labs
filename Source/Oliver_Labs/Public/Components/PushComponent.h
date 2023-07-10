// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PushComponent.generated.h"

class AOliver;
class APushableObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OLIVER_LABS_API UPushComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPushComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void BeginPush(APushableObject* PushableObject);
	UFUNCTION()
		void EndPush();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	APushableObject* CurrentPushable;

	UPROPERTY(EditDefaultsOnly)
		float PushSpeed;
	UPROPERTY(EditDefaultsOnly)
		float PushRange;

	UFUNCTION()
	void PushInteraction();

public:
// GETTERS
	FORCEINLINE UPushComponent* GetPushComponent() { return this; }
	FORCEINLINE float GetPushSpeed() { return PushSpeed; }
	FORCEINLINE float GetPushRange() { return PushRange; }
	FORCEINLINE bool GetIsPushingObject() const { return CurrentPushable ? true : false; }

};
