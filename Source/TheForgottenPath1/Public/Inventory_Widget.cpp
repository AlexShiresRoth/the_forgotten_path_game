// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Widget.h"
#include "InventoryItem.h"

// Player character inventory sets this
// TODO maybe there is a more efficient way to set inventory list in widget
void UInventory_Widget::SetInventoryItemsList(TArray<AInventoryItem *> InventoryItemsList)
{
    this->InventoryWidgetState.InventoryItemsList = InventoryItemsList;
    this->PopulateGridPanel();
}

// TODO create widget for each item in inventory
void UInventory_Widget::PopulateGridPanel()
{
    UE_LOG(LogTemp, Warning, TEXT("Inventory Items List: %d"), this->InventoryWidgetState.InventoryItemsList.Num());
    for (AInventoryItem *Item : this->InventoryWidgetState.InventoryItemsList)
    {
        if (Item)
        {
            if (Item->ItemName.IsEmpty() || Item->ItemQuantity <= 0 || Item->ItemImage == nullptr)
            {
                // Handle invalid input
                return;
            }

            UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *Item->ItemName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Item is null"));
        }
    }
}