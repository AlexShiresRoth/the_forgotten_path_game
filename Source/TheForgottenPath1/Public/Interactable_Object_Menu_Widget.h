// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "Components/GridPanel.h"
#include "Interactable_Object_Menu_Widget.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClickedDelegate);
class AInventoryItem;
class UInventoryItemWidget;
UCLASS()
class THEFORGOTTENPATH1_API UInteractable_Object_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HandleCloseButtonClicked();

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnCloseButtonClickedDelegate OnCloseButtonClicked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Object Data")
	FString ObjectName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Object Data")
	int32 ObjectID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Object Data")
	TArray<AInventoryItem *> ItemsList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory UI")
	TSubclassOf<UInventoryItemWidget> InventoryItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory UI", meta = (BindWidget))
	class UGridPanel *ItemsGrid;

	UFUNCTION(BlueprintCallable, Category = "Inventory UI")
	void RemoveItemFromList(UInventoryItemWidget *ItemWidget);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory UI")
	int MaxColumns = 5;

	UFUNCTION(BlueprintCallable, Category = "Inventory UI")
	void PopulateGridPanel();

	void SetCustomObjectData(FString Title, int32 ID);

	void SetCustomInventoryItemsList(TArray<AInventoryItem *> InventoryItemsList);
};
