// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../../Interfaces/InteractInterface.h"

#include "PushableObject.generated.h"


UCLASS()
class OLIVER_LABS_API APushableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APushableObject();

	UFUNCTION()
	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

private:


};
