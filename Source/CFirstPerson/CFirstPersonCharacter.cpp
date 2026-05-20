// Copyright Epic Games, Inc. All Rights Reserved.

#include "CFirstPersonCharacter.h"

#include "CActionInterface.h"
#include "CChest.h"
#include "CFirstPersonProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACFirstPersonCharacter

ACFirstPersonCharacter::ACFirstPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//LineLen = 200.0f;
}

//////////////////////////////////////////////////////////////////////////// Input

void ACFirstPersonCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACFirstPersonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACFirstPersonCharacter::Look);
		
		EnhancedInputComponent->BindAction(ActionAction, ETriggerEvent::Started, this, &ACFirstPersonCharacter::Action);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACFirstPersonCharacter::Server_CallAction_Implementation(FVector Direction)
{
	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	AActor *Hitting;
	
	FVector StartLine=FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLine=Direction*LineLen+StartLine;
	
	if (!GetWorld()) return;
	
	DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Green, false, 1, 0, 1);
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLine, EndLine, ECollisionChannel::ECC_Visibility,CollisionParams))
	{
		if (Hit.bBlockingHit)
		{
			Hitting=Hit.GetActor();
			UE_LOG(LogTemp, Warning, TEXT("Hitting: %s"), *Hit.GetActor()->GetName());
			ICActionInterface * ActionInterface = Cast<ICActionInterface>(Hitting);
			if(ActionInterface)
			{
				ActionInterface->IAction();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Hitting does NOT implement intergace"));
			}
			ACChest * CChest = Cast<ACChest>(Hitting);
			if (CChest)
			{
				if (!CChest->ChestDelegate.IsBound())
				{
					CChest->ChestDelegate.AddDynamic(this,&ACFirstPersonCharacter::Chest);
					UE_LOG(LogTemp, Warning, TEXT("Hitting Chest"));
				\
				}
			}
		}
	}
}



void ACFirstPersonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACFirstPersonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}void ACFirstPersonCharacter::Action(const FInputActionValue& Value)
{
	Server_CallAction(FirstPersonCameraComponent->GetForwardVector());
}

void ACFirstPersonCharacter::Chest()
{
	UE_LOG(LogTemp, Warning, TEXT("Delegate Chest"));
}
