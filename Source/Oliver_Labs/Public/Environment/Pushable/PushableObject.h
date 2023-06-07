// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PushableObject.generated.h"

class UBoxComponent;
class UPrimitiveComponent;

UCLASS()
class OLIVER_LABS_API APushableObject : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APushableObject();

	UFUNCTION()
		bool CanPush();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* CollisionComponent;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
