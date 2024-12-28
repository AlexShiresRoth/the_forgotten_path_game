// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

	// TODO this needs to match inventory item
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
	void SetItemData(FString Name, int Quantity, int32 ID, UTexture2D *Image);
};
