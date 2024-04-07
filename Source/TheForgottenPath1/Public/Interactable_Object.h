// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable_Object.generated.h"

UCLASS()
class THEFORGOTTENPATH1_API AInteractable_Object : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable_Object();

	UFUNCTION(BlueprintCallable, Category = Mesh)
	void GetMeshName();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorBeginCursorOver(AActor *TouchedActor);

	UFUNCTION()
	void OnActorEndCursorOver(AActor *TouchedActor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh component for visualization
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *MeshComponent;

	UMaterialInterface *CreateOutlineMaterial();
	void ApplyOutlineMaterial();
	void RevertMaterial();

	UPROPERTY(EditDefaultsOnly, Category = "Outline")
	UMaterialInterface *BaseMaterial;

	UMaterialInterface *OutlineMaterial;
	TArray<UMaterialInstanceDynamic *> DynamicMaterials;

	TMap<UStaticMeshComponent *, TArray<UMaterialInterface *>> OriginalMaterialsMap;
};
