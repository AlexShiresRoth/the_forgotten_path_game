// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable_Object.h"
#include "Blueprint/UserWidget.h"
// Sets default values
AInteractable_Object::AInteractable_Object()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = nullptr;
	BaseMaterial = nullptr;
	OutlineMaterial = nullptr;
}

void AInteractable_Object::GetMeshName()
{
	if (UStaticMeshComponent *Mesh = FindComponentByClass<UStaticMeshComponent>())
	{
		FString MeshName = Mesh->GetStaticMesh()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Mesh is set to %s"), *MeshName);
	}
}

// Called when the game starts or when spawned
void AInteractable_Object::BeginPlay()
{
	Super::BeginPlay();

	GetMeshName();

	// Get the mesh component
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();

	// Store the mesh component reference and base material
	if (MeshComponent)
	{
		BaseMaterial = MeshComponent->GetMaterial(0);

		// Make sure BaseMaterial exists before proceeding
		if (BaseMaterial)
		{
			// Create outline material
			OutlineMaterial = CreateOutlineMaterial();

			if (OutlineMaterial)
			{
				UE_LOG(LogTemp, Warning, TEXT("Outline material is set to %s"), *OutlineMaterial->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to create outline material"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshComponent is not valid"));
	}

	OnBeginCursorOver.AddDynamic(this, &AInteractable_Object::OnActorBeginCursorOver);
	OnEndCursorOver.AddDynamic(this, &AInteractable_Object::OnActorEndCursorOver);
}

void AInteractable_Object::OnActorBeginCursorOver(AActor *TouchedActor)
{
	if (TouchedActor == this && MeshComponent)
	{
		// Apply outline material to mesh component
		ApplyOutlineMaterial();
	}
}

void AInteractable_Object::OnActorEndCursorOver(AActor *TouchedActor)
{
	if (TouchedActor == this && MeshComponent)
	{
		// Revert material on mesh component
		RevertMaterial();
	}
}

void AInteractable_Object::ShowUIWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Show UI widget"));
	if (WidgetClass && !WidgetInstance)
	{
		// Create an instance of the UI widget
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

		// Check if the widget instance was created successfully
		if (WidgetInstance)
		{
			// Add the widget to the viewport
			WidgetInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create widget instance"));
		}
	}
}

void AInteractable_Object::HideUIWidget()
{
	if (WidgetInstance)
	{
		// Remove the widget from the viewport
		WidgetInstance->RemoveFromParent();

		// Reset the widget instance pointer
		WidgetInstance = nullptr;
	}
}

// Called every frame
void AInteractable_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			DynamicMaterial->SetVectorParameterValue(TEXT("OutlineColor"), FLinearColor::Red);
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
		// Apply the outline material to the mesh component
		UE_LOG(LogTemp, Warning, TEXT("Applying outline material %s"), *OutlineMaterial->GetName());
		MeshComponent->SetMaterial(0, OutlineMaterial);
	}
}

void AInteractable_Object::RevertMaterial()
{
	if (BaseMaterial && MeshComponent)
	{
		// Revert material on mesh component
		UE_LOG(LogTemp, Warning, TEXT("Reverting to base material %s"), *BaseMaterial->GetName());
		MeshComponent->SetMaterial(0, BaseMaterial);
	}
}
