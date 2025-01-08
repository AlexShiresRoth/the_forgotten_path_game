// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Inventory_Widget.generated.h"

/**
 *
 */
class AInventoryItem;

USTRUCT(BlueprintType)
struct FInventoryWidgetState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TArray<AInventoryItem *> InventoryItemsList;

	FInventoryWidgetState()
	{
	}
};

UCLASS()
class THEFORGOTTENPATH1_API UInventory_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetInventoryItemsList(TArray<AInventoryItem *> InventoryItemsList);

	UFUNCTION(BlueprintCallable, Category = "Inventory UI")
	void PopulateGridPanel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory UI", meta = (BindWidget))
	class UGridPanel *ItemsGrid;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory State")
	FInventoryWidgetState InventoryWidgetState;
};
