#include "Interactable_Object_Menu_Widget.h"
#include "InventoryItemWidget.h"
#include "Components/GridSlot.h"
#include "Components/SizeBox.h"
#include "InventoryItem.h"

void UInteractable_Object_Menu_Widget::HandleCloseButtonClicked()
{
    OnCloseButtonClicked.Broadcast();
}

void UInteractable_Object_Menu_Widget::PopulateGridPanel()
{

    for (int32 Index = 0; Index < ItemsList.Num(); Index++)
    {
        int32 Row = Index / MaxColumns;
        int32 Column = Index % MaxColumns;

        if (InventoryItemWidgetClass == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("InventoryItemWidgetClass is null"));
            return;
        }

        UInventoryItemWidget *ItemWidget = CreateWidget<UInventoryItemWidget>(GetWorld(), InventoryItemWidgetClass);

        if (ItemWidget)
        {
            ItemWidget->SetItemData(ItemsList[Index]->ItemName, ItemsList[Index]->ItemQuantity, ItemsList[Index]->ItemID, ItemsList[Index]->ItemImage);

            UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *ItemWidget->ItemName);

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

void UInteractable_Object_Menu_Widget::SetCustomObjectData(FString Title, int32 ID)
{
    if (Title != "")
    {
        ObjectName = Title;
    }
    if (ID > 0)
    {
        ObjectID = ID;
    }
}

void UInteractable_Object_Menu_Widget::SetCustomInventoryItemsList(TArray<AInventoryItem *> InventoryItemsList)
{
    if (InventoryItemsList.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Inventory Items List: %d"), InventoryItemsList.Num());
        ItemsList = InventoryItemsList;

        for (AInventoryItem *Item : ItemsList)
        {
            UE_LOG(LogTemp, Warning, TEXT("Inventory Item Name: %s"), *Item->ItemName);
            UE_LOG(LogTemp, Warning, TEXT("Inventory Item ID: %d"), Item->ItemID);
            UE_LOG(LogTemp, Warning, TEXT("Inventory Item Quantity: %d"), Item->ItemQuantity);
        }
    }
}
