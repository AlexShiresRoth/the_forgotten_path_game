#include "Interactable_Object_Menu_Widget.h"
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
