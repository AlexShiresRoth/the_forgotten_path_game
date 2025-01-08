// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.h"
#include "Interactable_Object.generated.h"

class UUserWidget;
class AInventoryItem;

// OBJECT STATE
USTRUCT(BlueprintType)
struct FInteractableObjectState
{
	GENERATED_BODY()

	// Track removed item IDs
	UPROPERTY(BlueprintReadWrite, Category = "State")
	TArray<FName> RemovedItemIDs;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bHasBeenInteractedWith = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 TimesAccessed = 0;

	// Constructor for default values
	FInteractableObjectState()
		: bHasBeenInteractedWith(false), TimesAccessed(0)
	{
	}
};

UCLASS()
class THEFORGOTTENPATH1_API AInteractable_Object : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable_Object();

	UFUNCTION()
	void OnMenuWidgetClosed();
	// This is called from the menu widget when an item is removed
	UFUNCTION()
	void RemoveItemFromObjectList(AInventoryItem *Item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Metadata")
	FString MeshTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Metadata")
	int32 MeshID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Metadata")
	TArray<AInventoryItem *> InventoryItemsList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	void ApplyOutlineMaterial();

	void RevertMaterial();

	// Mesh component for visualization
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Outline")
	UMaterialInterface *BaseMaterial;

	UMaterialInterface *CreateOutlineMaterial();

	UMaterialInterface *OutlineMaterial;
	TArray<UMaterialInstanceDynamic *> DynamicMaterials;

	TMap<UStaticMeshComponent *, TArray<UMaterialInterface *>> OriginalMaterialsMap;

	// OBJECT STATE
private:
	UPROPERTY(VisibleAnywhere, Category = "Object State")
	FInteractableObjectState ObjectState;
};
