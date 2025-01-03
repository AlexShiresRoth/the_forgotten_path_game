// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InventoryItem.h"
#include "InventoryItemMenuWidget.h"
#include "InventoryItemWidget.generated.h"

/**
 *
 */
class UInteractable_Object_Menu_Widget;

UCLASS()
class THEFORGOTTENPATH1_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	UTexture2D *ItemImage;

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	void SetItemData(AInventoryItem *Item);

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	void RenderHoverWidget();

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	void RemoveHoverWidget();

	UFUNCTION(BlueprintCallable, Category = "Item Data")
	void RemoveItemFromList(UInventoryItemWidget *ItemWidget);

	UPROPERTY(EditAnywhere, Category = "Item Data")
	TSubclassOf<class UInventoryItemMenuWidget> ItemMenuWidgetClass;

	UInventoryItemMenuWidget *ItemMenuWidgetInstance;

	// this is instantiated in the class on widget item creation
	UInteractable_Object_Menu_Widget *InteractableObjectMenuWidgetClass;

	void SetMenuWidgetReference(UInteractable_Object_Menu_Widget *MenuWidget);
};
