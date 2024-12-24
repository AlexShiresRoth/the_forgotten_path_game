// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{
    // Initialize default values
    ItemName = TEXT("Default Item");
    ItemID = 1;
    ItemIcon = nullptr;
}

void UInventoryItem::PrintItemInfo()
{
    if (!ItemName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *ItemName);
    }

    if (ItemID > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Item ID: %d"), ItemID);
    }

    if (ItemIcon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Item Icon: %s"), *ItemIcon->GetName());
    }
}
