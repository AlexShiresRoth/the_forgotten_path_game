#include "Interactable_Object_Menu_Widget.h"
#include "InventoryItemWidget.h"
#include "Components/GridSlot.h"
#include "Components/SizeBox.h"
#include "Interactable_Object.h"
#include "InventoryItem.h"

void UInteractable_Object_Menu_Widget::HandleCloseButtonClicked()
{
    OnCloseButtonClicked.Broadcast();
}

// This wil remove items from both the widget and the original list on interactable object
void UInteractable_Object_Menu_Widget::RemoveItemFromList(UInventoryItemWidget *ItemWidget)
{
    if (ItemWidget)
    {
        for (AInventoryItem *Item : ItemsList)
        {
            if (Item->ItemID == ItemWidget->ItemID)
            {
                if (InteractableObjectInstance)
                {
                    InteractableObjectInstance->RemoveItemFromObjectList(Item);
                    ItemsList.Remove(Item);
                    ItemWidget->DestroyWidget();
                }

                break;
            }
        }
    }
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
            ItemWidget->SetItemData(ItemsList[Index]);
            // this is needed so we can refer back to this class to remove items
            ItemWidget->SetMenuWidgetReference(this);

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
        ItemsList = InventoryItemsList;
    }
}

void UInteractable_Object_Menu_Widget::SetInteractableObjectInstance(AInteractable_Object *ObjectInstance)
{
    if (ObjectInstance)
    {
        this->InteractableObjectInstance = ObjectInstance;
    }
}
