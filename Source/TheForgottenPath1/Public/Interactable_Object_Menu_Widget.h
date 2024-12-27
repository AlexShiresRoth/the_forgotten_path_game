// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "Interactable_Object_Menu_Widget.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClickedDelegate);
class AInventoryItem;
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

	void SetCustomObjectData(FString Title, int32 ID);

	void SetCustomInventoryItemsList(TArray<AInventoryItem *> InventoryItemsList);
};
