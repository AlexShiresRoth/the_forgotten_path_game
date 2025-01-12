// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Widget.h"
#include "InventoryItem.h"
#include "InventoryItemWidget.h"
#include "Components/GridSlot.h"
#include "Components/SizeBox.h"

// Player character inventory sets this
// TODO maybe there is a more efficient way to set inventory list in widget
void UInventory_Widget::SetInventoryItemsList(TArray<AInventoryItem *> InventoryItemsList)
{
    this->InventoryWidgetState.InventoryItemsList = InventoryItemsList;
    this->PopulateGridPanel();
}

// This works but may want a different widget, since it's expecting to remove the widget on click from interactable object menu
void UInventory_Widget::PopulateGridPanel()
{
    UE_LOG(LogTemp, Warning, TEXT("Inventory Items List: %d"), this->InventoryWidgetState.InventoryItemsList.Num());
    for (int32 Index = 0; Index < this->InventoryWidgetState.InventoryItemsList.Num(); Index++)
    {
        int32 Row = Index / MaxColumns;
        int32 Column = Index % MaxColumns;

        if (InventoryItemWidgetClass == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("InventoryItemWidgetClass is null"));
            return;
        }
        // TODO create a widget for the actual inventory item, or maybe create it for the interactable object menu
        UInventoryItemWidget *ItemWidget = CreateWidget<UInventoryItemWidget>(GetWorld(), InventoryItemWidgetClass);

        if (ItemWidget)
        {
            ItemWidget->SetItemData(this->InventoryWidgetState.InventoryItemsList[Index]);
            // this is needed so we can refer back to this class to remove items
            ItemWidget->SetInventoryWidgetReference(this);

            if (ItemsGrid)
            {
                UGridSlot *GridSlot = ItemsGrid->AddChildToGrid(ItemWidget);

                if (GridSlot)
                {
                    GridSlot->SetRow(Row);
                    GridSlot->SetColumn(Column);

                    FMargin Margin = FMargin(10.0f, 10.0f, 10.0f, 10.0f);
                    GridSlot->SetPadding(Margin);
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("ItemsGrid is null"));
            }
        }
    }
}