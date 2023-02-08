// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Oliver.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"

// Sets default values
AOliver::AOliver()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

/* Core Components */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	/* Input */
	bIsCrouched = false;
}

// Called when the game starts or when spawned
void AOliver::BeginPlay()
{
	Super::BeginPlay();
	
	// Adding Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) // Creating Subsystem (UEnhancedInputLocalPlayerSubsystem) is what will allow you add mapping contexts, bind input delegates, and more.
		{
			Subsystem->AddMappingContext(OliverMappingContext, 0);
		}
	}
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
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AOliver::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AOliver::EndCrouch);
	}
} 

void AOliver::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>(); // Getting the X and Y values from our Input Action

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AOliver::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>(); // Getting the X and Y values from our Input Action

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AOliver::Jump()
{
	if (bIsCrouched) return;
	
	Super::Jump();
}

void AOliver::StartCrouch()
{
	if (!bIsCrouched)
	{
		Crouch();
		SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
		GetCharacterMovement()->MaxWalkSpeed = 150.f;
		
		bIsCrouched = true;
	}
}

void AOliver::EndCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
		SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		bIsCrouched = false;
	}
}
