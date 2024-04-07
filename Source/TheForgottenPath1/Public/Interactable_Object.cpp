// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable_Object.h"

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
	// Bind cursor over events to the actor
	OnBeginCursorOver.AddDynamic(this, &AInteractable_Object::OnActorBeginCursorOver);
	OnEndCursorOver.AddDynamic(this, &AInteractable_Object::OnActorEndCursorOver);

	// Get the mesh component
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();

	// Store the mesh component reference
	if (MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshComponent is valid"));

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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshComponent is not valid"));
	}
}

void AInteractable_Object::OnActorBeginCursorOver(AActor *TouchedActor)
{
	if (TouchedActor == this && MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnActorBeginCursorOver"));

		// Apply outline material to mesh component
		ApplyOutlineMaterial();
	}
}

void AInteractable_Object::OnActorEndCursorOver(AActor *TouchedActor)
{
	if (TouchedActor == this && MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnActorEndCursorOver"));

		// Revert material on mesh component
		RevertMaterial();
	}
}

// Called every frame
void AInteractable_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UMaterialInterface *AInteractable_Object::CreateOutlineMaterial()
{
	UMaterialInstanceDynamic *DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("OutlineWidth"), 0.2f);
		DynamicMaterial->SetVectorParameterValue(TEXT("OutlineColor"), FLinearColor::Red);
		return DynamicMaterial;
	}
	return nullptr;
}

void AInteractable_Object::ApplyOutlineMaterial()
{
	if (OutlineMaterial && MeshComponent)
	{
		// Store the current material
		BaseMaterial = MeshComponent->GetMaterial(0);

		// Create a dynamic material instance from the outline material
		UMaterialInstanceDynamic *DynamicMaterial = UMaterialInstanceDynamic::Create(OutlineMaterial, this);

		// Apply the dynamic material instance to the mesh component
		MeshComponent->SetMaterial(0, DynamicMaterial);

		// Store the dynamic material instance
		DynamicMaterials.Add(DynamicMaterial);
	}
}

void AInteractable_Object::RevertMaterial()
{
	if (BaseMaterial && MeshComponent)
	{
		// Revert material on mesh component
		MeshComponent->SetMaterial(0, BaseMaterial);

		// Clear dynamic materials array
		DynamicMaterials.Empty();
	}
}
