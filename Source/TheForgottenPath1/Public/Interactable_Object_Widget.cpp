#include "Interactable_Object_Widget.h"

void UInteractable_Object_Widget::SetCustomInteractableObjectData(FString ObjectTitle, int32 ObjectID)
{
    if (ObjectTitle != "")
    {
        Name = ObjectTitle;
    }
}
