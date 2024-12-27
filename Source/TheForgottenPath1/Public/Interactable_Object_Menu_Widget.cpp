#include "Interactable_Object_Menu_Widget.h"
#include "Item.h"
#include "Interactable_Object.h"

void UInteractable_Object_Menu_Widget::HandleCloseButtonClicked()
{
    OnCloseButtonClicked.Broadcast();
}

void UInteractable_Object_Menu_Widget::SetCustomInteractableObjectData(FString ObjectTitle, int32 ObjectID)
{
    if (ObjectTitle != "")
    {
        UE_LOG(LogTemp, Warning, TEXT("Object Name: %s"), *ObjectTitle);
        ObjectName = ObjectTitle;
    }
    else
    {
        ObjectName = TEXT("Unknown Object");
    }
}

void UInteractable_Object_Menu_Widget::SetCustomInventoryItemsList(TArray<AItem *> InventoryItemsList)
{
    if (InventoryItemsList.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Inventory Items List: %d"), InventoryItemsList.Num());
        ItemsList = InventoryItemsList;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Inventory Items List is empty"));
    }
}

void UInteractable_Object_Menu_Widget::RenderItemsList()
{
    if (ItemsList.Num() > 0)
    {
        for (AItem *Item : ItemsList)
        {

            if (Item)
            {
                UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *Item->ItemName);
                UE_LOG(LogTemp, Warning, TEXT("Item ID: %d"), Item->ItemID);

                // Optionally, destroy the instance if not needed
                // ItemInstance->Destroy();
            }
        }
    }
}
