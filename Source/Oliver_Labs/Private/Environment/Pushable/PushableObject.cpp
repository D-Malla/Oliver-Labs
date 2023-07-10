// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Pushable/PushableObject.h"

#include "Characters/Oliver.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PushComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h" 

#define PUSHFAILEDSTRING(String) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red, FString::Printf(TEXT(String)))

// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
}

void APushableObject::OnConstruction(const FTransform& Transform)
{
	int ArrowIndex = 0;
	for (FTransform Transforms : PushTransforms) // Iterating through TArray of PushTransforms. Each element within array will create an arrow component and it will point to it's forward direction.
	{
		Super::OnConstruction(Transform);

		ArrowComp = NewObject<UArrowComponent>(this, UArrowComponent::StaticClass(), FName("Arrow" + FString::FromInt(ArrowIndex)));
		check(ArrowComp);
		ArrowComp->RegisterComponent();
		//ArrowComp->SetHiddenInGame(false);
		ArrowComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		ArrowComp->SetRelativeTransform(Transforms);
		ArrowComp->SetArrowColor(FColor::Red);
		ArrowComp->ArrowLength = ArrowLength;
		ArrowComp->ArrowSize = ArrowSize;

		ArrowIndex++;
	}
}

// Called when the game starts or when spawned
void APushableObject::BeginPlay()
{
	Super::BeginPlay();

}

void APushableObject::Interact(ACharacter* Character)
{
	AOliver* Oliver = Cast<AOliver>(Character);
	if (!Oliver->GetIsPushing())
	{
		if (Oliver && Oliver->GetComponentByClass(UPushComponent::StaticClass()))
		{
			UPushComponent* PushComponent = Oliver->PushComponent->GetPushComponent();
			FVector2D Oliver2DLocation = FVector2D(Oliver->GetActorLocation().X, Oliver->GetActorLocation().Y);
			int BestIndex = FindClosestPushTransformIndex(Oliver2DLocation, PushComponent->GetPushRange()); //BestIndex == Closest Transform

			if (BestIndex >= 0)
			{
				FTransform PushTransformIndex = PushTransforms[BestIndex];
			
				FTransform ComposedTransforms = PushTransformIndex * GetPushableObject()->GetActorTransform();
				float OliverCapsuleHalfHeight = Oliver->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

				FTransform OliverNewTransform = ComposedTransforms; // Variable to hold Oliver's new transform
				OliverNewTransform.SetLocation(ComposedTransforms.GetLocation() + FVector(0.f, 0.f, OliverCapsuleHalfHeight));

				FVector Center = OliverNewTransform.GetLocation(); // This is the point where Oliver's hips should be placed when pushing

				DrawDebugSphere(GetWorld(), Center, 20.f, 12, FColor::Red, false, 2.f, 0U, 1.f);

				// Sweep variables
				FHitResult HitResult;
				FVector SweepStart = OliverNewTransform.GetLocation() + FVector(0.f, 0.f, 70.f);
				FVector SweepEnd = OliverNewTransform.GetLocation() + FVector(0.f, 0.f, 100.f);

				FCollisionShape CollisionShape;
				float OliverCapsuleRadius = Oliver->GetCapsuleComponent()->GetScaledCapsuleRadius();
				CollisionShape.SetCapsule(OliverCapsuleRadius, OliverCapsuleHalfHeight);

				FCollisionQueryParams Params;
			
				GetWorld()->SweepSingleByChannel(HitResult, SweepStart, SweepEnd, OliverNewTransform.GetRotation(), ECollisionChannel::ECC_Visibility, CollisionShape);

				// Checking if there is room to push
				if (!HitResult.bStartPenetrating)
				{
					// Checking if surface is not too steep to walk
					if (HitResult.ImpactNormal.Z < Oliver->GetCharacterMovement()->GetWalkableFloorZ())
					{
						FHitResult TraceHitResult;
						FCollisionQueryParams TraceQueryParams;
						TraceQueryParams.AddIgnoredActor(this);
					
						GetWorld()->LineTraceSingleByChannel(TraceHitResult, GetActorLocation(), OliverNewTransform.GetLocation(), ECC_Visibility,TraceQueryParams);
						if (!TraceHitResult.bBlockingHit)
						{
							Oliver->SetActorTransform(OliverNewTransform, false, nullptr, ETeleportType::TeleportPhysics);

							Oliver->SpringArmComponent->bUsePawnControlRotation = false;
							PushComponent->BeginPush(this);
						}
						else
						{
							PUSHFAILEDSTRING("Wall in between character and object");
						}
					}
					else
					{
						PUSHFAILEDSTRING("Floor not walkable");
					}
				}
				else
				{
					PUSHFAILEDSTRING("No room to stand");
				}
			}
			else
			{
				PUSHFAILEDSTRING("No push transform found");
			}
		}
		else
		{
			PUSHFAILEDSTRING("Oliver is invalid OR Oliver doesn't have PushComponent");
		}
	}
	else
	{
		if (Oliver && Oliver->GetComponentByClass(UPushComponent::StaticClass()))
		{

			Oliver->SpringArmComponent->bUsePawnControlRotation = true;
			Oliver->PushComponent->EndPush();
		}
	}
}

int APushableObject::FindClosestPushTransformIndex(FVector2D CharacterLocation, float PushRange)
{
	AOliver* Oliver = Cast<AOliver>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	float CurrentTransformIndex = 0;
	int ClosestTransformIndex = -1;
	float ClosestDistanceSq = 0.f;

	for (FTransform Transforms : PushTransforms)
	{
		FVector WorldSpaceTransformLocation = UKismetMathLibrary::TransformLocation(GetPushableObject()->GetActorTransform(), Transforms.GetLocation()); // Converting each transform's location from Local space to World space.
		// Getting the 2D coordinates of the transforms/Oliver (X,Y)
		FVector2D WorldTransformLocation2D = FVector2D(WorldSpaceTransformLocation);
		FVector2D PlayerLocation2D = FVector2D(Oliver->GetActorLocation());

		float CurrentDistanceSq = UKismetMathLibrary::DistanceSquared2D(PlayerLocation2D, WorldTransformLocation2D);

		if (CurrentDistanceSq < FMath::Square(PushRange))
		{

			if (CurrentDistanceSq < ClosestDistanceSq || ClosestTransformIndex < 0)
			{
				ClosestTransformIndex = CurrentTransformIndex;
				ClosestDistanceSq = CurrentDistanceSq;
			}
		}
		CurrentTransformIndex++;
	}
	return ClosestTransformIndex;
}
