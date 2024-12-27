#include "Interactable_Object_Menu_Widget.h"
#include "InventoryItem.h"

void UInteractable_Object_Menu_Widget::HandleCloseButtonClicked()
{
    OnCloseButtonClicked.Broadcast();
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
