// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable_Object.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable_Object_Widget.h"
#include "Interactable_Object_Menu_Widget.h"
#include "TheForgottenPath1/TheForgottenPath1Character.h"

// Sets default values
AInteractable_Object::AInteractable_Object()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = nullptr;
	BaseMaterial = nullptr;
	OutlineMaterial = nullptr;
}

// Called every frame
void AInteractable_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable_Object::BeginPlay()
{
	Super::BeginPlay();

	// Get the mesh component
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();

	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshComponent is not valid"));
		return;
	}

	BaseMaterial = MeshComponent->GetMaterial(0);
	if (!BaseMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseMaterial is not valid"));
	}

	OutlineMaterial = CreateOutlineMaterial();
	if (!OutlineMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create outline material"));
	}

	MeshComponent->OnClicked.AddDynamic(this, &AInteractable_Object::OnMeshClicked);

	if (!OnBeginCursorOver.IsBound())
	{
		OnBeginCursorOver.AddDynamic(this, &AInteractable_Object::OnActorBeginCursorOver);
	}

	if (!OnEndCursorOver.IsBound())
	{
		OnEndCursorOver.AddDynamic(this, &AInteractable_Object::OnActorEndCursorOver);
	}
}

void AInteractable_Object::OnActorBeginCursorOver(AActor *TouchedActor)
{
	if (!TouchedActor || !MeshComponent || TouchedActor != this)
	{
		return;
	}

	ApplyOutlineMaterial();

	if (!MeshTitle.IsEmpty() && MeshID > 0)
	{
		ShowUIWidget();
	}
}

void AInteractable_Object::OnActorEndCursorOver(AActor *TouchedActor)
{
	if (TouchedActor != this || !MeshComponent)
	{
		return;
	}

	if (TouchedActor == this && MeshComponent)
	{
		// Revert material on mesh component
		RevertMaterial();

		HideUIWidget();
	}
}

// TODO: Remove player damage, just needed for testing
void AInteractable_Object::OnMeshClicked(UPrimitiveComponent *ClickedComp, FKey ButtonClicked)
{
	ShowUIMenuWidget();

	// get player character
	ATheForgottenPath1Character *PlayerCharacter = Cast<ATheForgottenPath1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter)
	{
		// testplayer damage
		float CurrentHealth = PlayerCharacter->GetCharacterCurrentHealth();
		PlayerCharacter->SetCharacterCurrentHealth(CurrentHealth - 1.f);
		UE_LOG(LogTemp, Warning, TEXT("Player damaged %f"), CurrentHealth);
	}
}

// TODO: Refactor this function, break out into smaller functions
void AInteractable_Object::ShowUIMenuWidget()
{
	if (MenuWidgetInstance)
	{
		return;
	}

	if (MenuWidgetClass)
	{
		// Create a new instance of the menu widget
		MenuWidgetInstance = CreateWidget<UInteractable_Object_Menu_Widget>(GetWorld(), MenuWidgetClass);
		if (MenuWidgetInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Menu widget instance created"));

			UInteractable_Object_Menu_Widget *MenuWidget = Cast<UInteractable_Object_Menu_Widget>(MenuWidgetInstance);

			if (MenuWidget)
			{
				MenuWidget->SetCustomInteractableObjectData(MeshTitle, MeshID);

				MenuWidget->OnCloseButtonClicked.AddDynamic(this, &AInteractable_Object::OnMenuWidgetClosed);

				// Render the items list if there are any

				if (InventoryItemsList.Num() > 0)
				{
					MenuWidget->SetCustomInventoryItemsList(InventoryItemsList);
				}
			}

			MenuWidgetInstance->AddToViewport();
		}
	}
}

// Called from inside the menu widget blueprint's button
void AInteractable_Object::OnMenuWidgetClosed()
{
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}
}

void AInteractable_Object::ShowUIWidget()
{

	if (WidgetClass && !WidgetInstance)
	{
		// Create an instance of the UI widget
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

		// Check if the widget instance was created successfully
		if (WidgetInstance)
		{
			// Set data on the hover menu widget
			UInteractable_Object_Widget *Widget = Cast<UInteractable_Object_Widget>(WidgetInstance);
			if (Widget)
			{
				Widget->SetCustomInteractableObjectData(MeshTitle, MeshID);
			}

			WidgetInstance->AddToViewport();

			FVector MeshLocation = GetActorLocation();

			FVector2D ScreenLocation;

			UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), MeshLocation, ScreenLocation);

			// Add the widget to the viewport
			WidgetInstance->SetPositionInViewport(ScreenLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create widget instance"));
		}
	}
}

void AInteractable_Object::HideUIWidget()
{
	if (WidgetInstance && WidgetInstance != nullptr)
	{
		// Remove the widget from the viewport
		WidgetInstance->RemoveFromParent();

		// Reset the widget instance pointer
		WidgetInstance = nullptr;
	}
}

UMaterialInterface *AInteractable_Object::CreateOutlineMaterial()
{
	if (BaseMaterial)
	{
		// Create a dynamic material instance from the base material
		UMaterialInstanceDynamic *DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);

		if (DynamicMaterial)
		{
			// Modify dynamic material parameters for outline effect
			DynamicMaterial->SetScalarParameterValue(TEXT("OutlineWidth"), 0.2f);
			// DynamicMaterial->SetVectorParameterValue(TEXT("OutlineColor"), FLinearColor::Red);
			return DynamicMaterial;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material instance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseMaterial is not valid"));
	}

	return nullptr;
}

void AInteractable_Object::ApplyOutlineMaterial()
{
	if (OutlineMaterial && MeshComponent)
	{
		MeshComponent->SetMaterial(0, OutlineMaterial);
	}
}

void AInteractable_Object::RevertMaterial()
{
	if (BaseMaterial && MeshComponent)
	{
		MeshComponent->SetMaterial(0, BaseMaterial);
	}
}
