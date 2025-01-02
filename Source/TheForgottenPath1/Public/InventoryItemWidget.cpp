// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItemWidget.h"

void UInventoryItemWidget::SetItemData(FString Name, int Quantity, int32 ID, UTexture2D *Image)
{
    if (Name.IsEmpty() || Quantity <= 0 || Image == nullptr)
    {
        // Handle invalid input
        return;
    }

    // Assign the values
    ItemName = Name;
    ItemQuantity = Quantity;
    ItemID = ID;
    ItemImage = Image;
}

void UInventoryItemWidget::RenderHoverWidget()
{
    if (ItemMenuWidgetClass)
    {
        ItemMenuWidgetInstance = CreateWidget<UInventoryItemMenuWidget>(GetWorld(), ItemMenuWidgetClass);

        UE_LOG(LogTemp, Warning, TEXT("Is this bveing called?"));

        if (ItemMenuWidgetInstance)
        {
            ItemMenuWidgetInstance->SetMenuData(ItemName);

            ItemMenuWidgetInstance->AddToViewport();

            UE_LOG(LogTemp, Warning, TEXT("This should work?"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Hover menu instance is invalid"))
        }
    }
}
