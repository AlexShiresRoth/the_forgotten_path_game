#include "Interactable_Object_Menu_Widget.h"

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
