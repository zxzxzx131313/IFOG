// Copyright Epic Games, Inc. All Rights Reserved.

#include "IFOGCharacter.h"

#include "BDOManager.h"
#include "IFOGProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IFogComponent.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AIFOGCharacter

AIFOGCharacter::AIFOGCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

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

	FogComponent = CreateDefaultSubobject<UIFogComponent>(TEXT("FogComponent"));
	FogComponent->SetupAttachment(GetCapsuleComponent());

}

void AIFOGCharacter::BeginPlay()
{
	// Call the base class

	Super::BeginPlay();

	FogComponent->SetRelativeScale3D(FVector(ScaleX, ScaleY, ScaleZ));
	FogComponent->SetRelativeLocation(FVector(0.0, ScaleY / 2.0, 0.0));
	UpdateFogComponentOpacity(0.03);
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


	FVector Loc = GetActorLocation();
	AActor* spawned = GetWorld()->SpawnActor(ABDOManager::StaticClass(), &Loc);
	BDOManager = (ABDOManager*)spawned;
	
	for (int i = 0; i < BDOCount; i++)
	{
		ABDO* Spawned = (ABDO*)BDOManager->SpawnActor();
		if (Spawned == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn BDO."));
		}
		else
		{
			Spawned->OnNearPlayer.AddDynamic(this, &AIFOGCharacter::UpdateFogComponentOpacity);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AIFOGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIFOGCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIFOGCharacter::Look);
	}
}

void AIFOGCharacter::UpdateFogComponentOpacity(float PlayerFogOpacity)
{
	FogComponent->UpdateFogOpacity(PlayerFogOpacity);
}


void AIFOGCharacter::Move(const FInputActionValue& Value)
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

void AIFOGCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AIFOGCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AIFOGCharacter::GetHasRifle()
{
	return bHasRifle;
}
