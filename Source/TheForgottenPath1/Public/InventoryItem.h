#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * Example UObject class for inventory items
 */

// TODO: change this to an aactor class in order to place items at build time
UCLASS(Blueprintable, BlueprintType)
class THEFORGOTTENPATH1_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	// Constructor
	UInventoryItem();

	// Example property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D *ItemIcon;

	// Example method
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PrintItemInfo();
};
