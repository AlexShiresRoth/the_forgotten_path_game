// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItemWidget.h"
#include "InventoryItem.h"
#include "Interactable_Object_Menu_Widget.h"

void UInventoryItemWidget::SetItemData(AInventoryItem *Item)
{
    if (Item->ItemName.IsEmpty() || Item->ItemQuantity <= 0 || Item->ItemImage == nullptr)
    {
        // Handle invalid input
        return;
    }

    // Assign the values
    ItemName = Item->ItemName;
    ItemQuantity = Item->ItemQuantity;
    ItemID = Item->ItemID;
    ItemImage = Item->ItemImage;
}

void UInventoryItemWidget::RenderHoverWidget()
{
    if (ItemMenuWidgetClass)
    {
        ItemMenuWidgetInstance = CreateWidget<UInventoryItemMenuWidget>(GetWorld(), ItemMenuWidgetClass);

        if (ItemMenuWidgetInstance)
        {
            ItemMenuWidgetInstance->SetMenuData(ItemName);

            ItemMenuWidgetInstance->AddToViewport();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Hover menu instance is invalid"))
        }
    }
}

void UInventoryItemWidget::RemoveHoverWidget()
{
    if (ItemMenuWidgetInstance)
    {
        ItemMenuWidgetInstance->RemoveFromViewport();
        ItemMenuWidgetInstance = nullptr;
    }
}

void UInventoryItemWidget::RemoveItemFromList(UInventoryItemWidget *ItemWidget)
{
    if (ItemWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemWidget is not null %s"), *ItemWidget->ItemName);

        if (InteractableObjectMenuWidgetClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("InteractableObjectMenuWidgetClass is not null %s"), *InteractableObjectMenuWidgetClass->ObjectName);

            InteractableObjectMenuWidgetClass->RemoveItemFromList(ItemWidget);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemWidget is null"));
    }
}

void UInventoryItemWidget::SetMenuWidgetReference(UInteractable_Object_Menu_Widget *MenuWidget)
{
    if (MenuWidget)
    {
        InteractableObjectMenuWidgetClass = MenuWidget;
    }
}
