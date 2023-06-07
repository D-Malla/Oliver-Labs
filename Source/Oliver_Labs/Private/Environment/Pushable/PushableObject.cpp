// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Pushable/PushableObject.h"

#include "Characters/Oliver.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	//CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	//CollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APushableObject::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &APushableObject::OnHit);
}

void APushableObject::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AOliver* Oliver = Cast<AOliver>(OtherActor);

	FVector OliverFWDVector = Oliver->GetActorForwardVector();
	FVector PushableDirection(roundf(OliverFWDVector.X), roundf(OliverFWDVector.Y),	roundf(OliverFWDVector.Z));

	if (CanPush())
	{
		//Oliver->GetCharacterMovement()->DisableMovement();

	
	}
}

bool APushableObject::CanPush()
{
	// Can get reference to player. 
	AOliver* Oliver = Cast<AOliver>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Oliver);

	FVector StartLocation = Oliver->GetActorLocation();
	FVector EndLocation = StartLocation + (Oliver->GetActorForwardVector() * 100.f);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, true);
	AttachToActor(Oliver, AttachmentRules);

	if (HitResult.GetActor() == this)
	{
		return true;
	}

	return false;
}