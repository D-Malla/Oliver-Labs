// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PushComponent.h"

#include "Characters/Oliver.h"
#include "Environment/Pushable/PushableObject.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
 
// Sets default values for this component's properties
UPushComponent::UPushComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PushSpeed = 60.f;
	PushRange = 120.f;
}

// Called when the game starts
void UPushComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);
	
}

// Called every frame
void UPushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentPushable)
	{
		FVector TickPushSpeed = GetOwner()->GetActorForwardVector() * (PushSpeed * DeltaTime);

		CurrentPushable->AddActorWorldOffset(TickPushSpeed, true);
	}
}

void UPushComponent::PushInteraction()
{
	if (GEngine)
	{	
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString(TEXT("Ticking!")));
	}
}

void UPushComponent::BeginPush(APushableObject* PushableObject)
{
	if (!CurrentPushable)
	{
		AOliver* Oliver = Cast<AOliver>(GetOwner());
		CurrentPushable = PushableObject;
		Oliver->SetIsPushing(true);

		FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, true);

		Oliver->AttachToActor(CurrentPushable, TransformRules);

		UPawnMovementComponent* OliverMovementComponent = Oliver->GetMovementComponent();
		OliverMovementComponent->bConstrainToPlane = true;
		OliverMovementComponent->ConstrainNormalToPlane(Oliver->GetActorRightVector());
		Oliver->GetCharacterMovement()->bOrientRotationToMovement = false;

		SetComponentTickEnabled(true);
	}

}

void UPushComponent::EndPush()
{
	if (CurrentPushable)
	{
		CurrentPushable = nullptr;
		
		AOliver* Oliver = Cast<AOliver>(GetOwner());
		UPawnMovementComponent* OliverMovementComponent = Oliver->GetMovementComponent();

		Oliver->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OliverMovementComponent->bConstrainToPlane = false;
		Oliver->GetCharacterMovement()->bOrientRotationToMovement = true;
		Oliver->SetIsPushing(false);
		SetComponentTickEnabled(false);
	}
}
