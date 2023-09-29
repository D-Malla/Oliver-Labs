// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Oliver.h"

#include "Characters/OliverPlayerController.h"
#include "Components/PushComponent.h"
#include "Environment/Doors/ButtonDoor.h"
#include "Environment/Pushable/PushableObject.h"
#include "HUD/DoorButtonWidget.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AOliver::AOliver()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.3f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

/* Core Components */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	PushComponent = CreateDefaultSubobject<UPushComponent>(TEXT("PushComponent"));

	/* Input */
	bIsCrouched = false;
	bCanPressButton = false;
	bIsPushing = false;

	ButtonDoor = nullptr;
	ButtonVolume = nullptr;
	PushableObject = nullptr;
}

// Called when the game starts or when spawned
void AOliver::BeginPlay()
{
	Super::BeginPlay();

	
	OliverPlayerController = Cast<AOliverPlayerController>(GetWorld()->GetFirstPlayerController());
	
	// Adding Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) // Creating Subsystem (UEnhancedInputLocalPlayerSubsystem) is what will allow you add mapping contexts, bind input delegates, and more.
		{
			Subsystem->AddMappingContext(OliverMappingContext, 0);
		}
	}

	UCapsuleComponent* OliverCollision = this->GetCapsuleComponent();
}

// Called every frame
void AOliver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

/* Input */
// Called to bind functionality to input
void AOliver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Enhanced Input Component
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) // Casting PlayerInputComponent into EnhancedInputComponent
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AOliver::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOliver::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AOliver::Jump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AOliver::ToggleCrouch);
		EnhancedInputComponent->BindAction(ButtonPressAction, ETriggerEvent::Started, this, &AOliver::PressButton);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AOliver::InteractWithObject);
	}
} 

void AOliver::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>(); // Getting the X and Y values from our Input Action

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	if (!PushComponent->GetIsPushingObject())
	{
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	};
}

void AOliver::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>(); // Getting the X and Y values from our Input Action

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AOliver::Jump()
{
	if (!PushComponent->GetIsPushingObject())
	{
		if (bIsCrouched) return;
	}

	Super::Jump();
}

void AOliver::ToggleCrouch()
{
	if (!PushComponent->GetIsPushingObject())
	{
		if (!bIsCrouched)
		{
			Crouch();
			SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
			GetCharacterMovement()->MaxWalkSpeed = 150.f;
			bIsCrouched = true;
		}
		else if (bIsCrouched)
		{
			UnCrouch();
			SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
			GetCharacterMovement()->MaxWalkSpeed = 300.f;
			bIsCrouched = false;
		}
	}
}

void AOliver::PressButton()
{
	if (!PushComponent->GetIsPushingObject())
	{
		if (bCanPressButton && ButtonPressAnimMontage && ButtonVolume)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			AnimInstance->Montage_Play(ButtonPressAnimMontage);
			ButtonDoor->SetIsDoorLocked(false);
			bCanPressButton = false;
			OliverPlayerController->RemoveButtonDoorHUD();
		}
	}
}

void AOliver::InteractWithObject()
{
		UWorld* WorldREF = GetWorld();
		FVector Center = GetActorLocation() - FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());	// Getting the foot location of character for sphere trace
		float SphereRadius = PushComponent->GetPushRange();

		// Initializing TArray variables for sphere trace arguments
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		TArray<AActor*> OutActors;

		DrawDebugSphere(GetWorld(), Center, SphereRadius, 12, FColor::White, false, 2.f, 0U, 1.f);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Center, SphereRadius, ObjectTypes, nullptr, ActorsToIgnore, OutActors);

		// Checking if any object within sphere radius inherits IInteractInterface. If it does...Interact()
		for (int i = 0; i < OutActors.Num(); i++)
		{
			if (IInteractInterface* InteractInterface = Cast<IInteractInterface>(OutActors[i]))
			{
				InteractInterface->Interact(this);
				break;
			}
		}
}
