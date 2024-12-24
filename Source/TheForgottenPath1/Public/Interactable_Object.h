// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.h"
#include "Interactable_Object.generated.h"

class UUserWidget;
class UInventoryItem;
UCLASS()
class THEFORGOTTENPATH1_API AInteractable_Object : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable_Object();

	UUserWidget *GetWidgetInstance() const { return WidgetInstance; }

	UFUNCTION()
	void OnMenuWidgetClosed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Metadata")
	FString MeshTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Metadata")
	int32 MeshID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Metadata")
	TArray<UInventoryItem *> Items;

protected:
	// Called when the game starts or when spawned
	virtual void
	BeginPlay() override;

	UFUNCTION()
	void OnActorBeginCursorOver(AActor *TouchedActor);

	UFUNCTION()
	void OnActorEndCursorOver(AActor *TouchedActor);

	UFUNCTION()
	void OnMeshClicked(UPrimitiveComponent *ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void ShowUIMenuWidget();

	UFUNCTION()
	void ShowUIWidget();

	UFUNCTION()
	void HideUIWidget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UUserWidget *MenuWidgetInstance;

	// Member variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget *WidgetInstance;

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
