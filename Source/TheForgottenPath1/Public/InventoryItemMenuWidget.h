// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "InventoryItemMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API UInventoryItemMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString ItemNameDisplay;

	void SetMenuData(FString ItemName);
};
