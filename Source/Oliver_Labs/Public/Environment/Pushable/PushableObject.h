// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../../Interfaces/InteractInterface.h"

#include "PushableObject.generated.h"

class AOliver;

class UArrowComponent;

UCLASS()
class OLIVER_LABS_API APushableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APushableObject();
	void OnConstruction(const FTransform& Transform) override;

	UPROPERTY()
		UArrowComponent* ArrowComp; // ArrowComponent attached to each of the transforms within PushTransforms array.


	UFUNCTION()
		virtual void Interact(ACharacter* Character) override;
	UFUNCTION()
		int FindClosestPushTransformIndex(FVector2D CharacterLocation, float PushRange);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float ArrowSize = 1.f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float ArrowLength = 40.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Meta = (MakeEditWidget = true, ExposeOnSpawn = "true", AllowPrivateAccess = "true"))
		TArray<FTransform> PushTransforms = {};

public:
	// GETTERS
	APushableObject* GetPushableObject() { return this; }
	TArray<FTransform> GetPushTransforms() { return PushTransforms; }
};
