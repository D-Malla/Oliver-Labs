// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OliverAnimInstance.generated.h"

class AOliver;

UCLASS()
class OLIVER_LABS_API UOliverAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UOliverAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/* Movement Properties */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties")
	AOliver* PlayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties")
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties")
	bool bIsCrouched;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties")
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties")
	bool bIsPushing;

	UFUNCTION(BlueprintCallable, Category = "Animations")
	virtual void UpdateAnimProperties();
};
