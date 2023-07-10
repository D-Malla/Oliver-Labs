// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/OliverAnimInstance.h"
#include "Characters/Oliver.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UOliverAnimInstance::UOliverAnimInstance()
{
	// Initialize Properties
	Speed = 0.f;
	bIsCrouched = false;
	bIsInAir = false;
}

void UOliverAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerReference = Cast<AOliver>(TryGetPawnOwner());
}

void UOliverAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerReference)
	{
		UpdateAnimProperties();
	}
}

void UOliverAnimInstance::UpdateAnimProperties()
{
	Speed = PlayerReference->GetVelocity().Size();
	bIsCrouched = PlayerReference->GetIsCrouched();
	bIsInAir = PlayerReference->GetMovementComponent()->IsFalling();
	bIsPushing = PlayerReference->GetIsPushing();
}
