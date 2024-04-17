#include "Interactable_Object_Widget.h"
#include "Interactable_Object.h"

void UInteractable_Object_Widget::SetCustomInteractableObjectData(FString ObjectTitle, int32 ObjectID)
{
    if (ObjectTitle != "")
    {
        Name = ObjectTitle;
    }
}
