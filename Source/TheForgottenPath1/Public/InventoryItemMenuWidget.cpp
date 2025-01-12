// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItemMenuWidget.h"
#include "InventoryItem.h"

void UInventoryItemMenuWidget::SetMenuData(FString ItemName)
{
    if (ItemName != "")
    {
        ItemNameDisplay = ItemName;
    }
}