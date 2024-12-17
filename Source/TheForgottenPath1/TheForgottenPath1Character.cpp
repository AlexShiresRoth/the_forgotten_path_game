// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheForgottenPath1Character.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Hero_Character_Widget.h"
#include "Menu_Widget.h"
#include "Inventory_Widget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheForgottenPath1Character

ATheForgottenPath1Character::ATheForgottenPath1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;			 // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;		// The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;								// Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATheForgottenPath1Character::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController *PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		// Show widget that contains health and other things
		ShowCharacterWidget();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheForgottenPath1Character::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheForgottenPath1Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheForgottenPath1Character::Look);

		// Main Menu
		EnhancedInputComponent->BindAction(MainMenuAction, ETriggerEvent::Triggered, this, &ATheForgottenPath1Character::ToggleMainMenuWidget);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ATheForgottenPath1Character::ToggleInventoryWidget);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATheForgottenPath1Character::EnterRagdoll()
{
	GetCharacterMovement()->DisableMovement();

	DetachFromControllerPendingDestroy();

	if (USkeletalMeshComponent *SkelMesh = GetMesh())
	{
		SkelMesh->SetSimulatePhysics(true);
		SkelMesh->SetCollisionProfileName(TEXT("Ragdoll"));
	}
}

void ATheForgottenPath1Character::Move(const FInputActionValue &Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATheForgottenPath1Character::Look(const FInputActionValue &Value)
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

void ATheForgottenPath1Character::SetMouseCursorVisible(bool bVisible)
{
	APlayerController *PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = bVisible;
	}
}

void ATheForgottenPath1Character::ShowCharacterWidget()
{
	if (CharacterWidgetClass)
	{
		CharacterWidgetInstance = CreateWidget<UHero_Character_Widget>(GetWorld(), CharacterWidgetClass);

		if (CharacterWidgetInstance)
		{
			UHero_Character_Widget *CharacterWidget = Cast<UHero_Character_Widget>(CharacterWidgetInstance);

			CharacterWidgetInstance->AddToViewport();
		}
	}
}

void ATheForgottenPath1Character::ToggleMainMenuWidget()
{
	if (!MainMenuWidgetClass)
		return;

	if (!MainMenuWidgetInstance)
	{
		// Create the widget if it doesn't exist
		MainMenuWidgetInstance = CreateWidget<UMenu_Widget>(GetWorld(), MainMenuWidgetClass);

		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			UE_LOG(LogTemp, Log, TEXT("MainMenuWidgetInstance Widget Added to Viewport"));
		}
		return;
	}
	else
	{
		// Check if widget is visible and remove it
		if (MainMenuWidgetInstance->IsInViewport())
		{
			MainMenuWidgetInstance->RemoveFromParent();
			MainMenuWidgetInstance = nullptr; // Destroy instance
			UE_LOG(LogTemp, Log, TEXT("MainMenuWidgetInstancey Widget Removed from Viewport"));
			return;
		}
	}
}

void ATheForgottenPath1Character::ToggleInventoryWidget()
{
	if (!InventoryWidgetClass)
		return;

	// Check if the widget instance is already created
	if (!InventoryWidgetInstance)
	{
		// Create the widget if it doesn't exist
		InventoryWidgetInstance = CreateWidget<UInventory_Widget>(GetWorld(), InventoryWidgetClass);

		if (InventoryWidgetInstance && !InventoryWidgetInstance->IsInViewport())
		{
			InventoryWidgetInstance->AddToViewport();
			UE_LOG(LogTemp, Log, TEXT("Inventory Widget Added to Viewport"));
		}
		return;
	}
	else
	{
		// Check if widget is visible and remove it
		if (InventoryWidgetInstance->IsInViewport())
		{
			InventoryWidgetInstance->RemoveFromParent();
			InventoryWidgetInstance = nullptr; // Destroy instance
			UE_LOG(LogTemp, Log, TEXT("Inventory Widget Removed from Viewport"));
			return;
		}
	}
}

float ATheForgottenPath1Character::GetCharacterCurrentHealth()
{
	return CharacterCurrentHealth;
}

// This does update the ui but it's a little clunky. Refactor and fix it up
// How to update the player once death
float ATheForgottenPath1Character::SetCharacterCurrentHealth(float NewHealth)
{
	CharacterCurrentHealth = NewHealth;
	if (CharacterWidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character widget instance created"));

		UHero_Character_Widget *CharWidget = Cast<UHero_Character_Widget>(CharacterWidgetInstance);

		if (CharWidget)
		{
			if (CharacterCurrentHealth <= 0)
			{
				bIsDead = true;
				CharWidget->UpdateHealthUI(0.f);
				CharWidget->UpdateDeathText("You've Died :(");

				EnterRagdoll();
				return 0.f;
			}
			CharWidget->UpdateHealthUI(CharacterCurrentHealth);
		}
	}
	return CharacterCurrentHealth;
}
