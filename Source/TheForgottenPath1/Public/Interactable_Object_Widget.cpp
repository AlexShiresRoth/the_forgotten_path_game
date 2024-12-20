#include "Interactable_Object_Widget.h"
#include "Interactable_Object.h"

void UInteractable_Object_Widget::SetCustomInteractableObjectData(FString ObjectTitle, int32 ObjectID)
{
    if (ObjectTitle != "")
    {
        Name = ObjectTitle;
    }
}

FString UInteractable_Object_Widget::GetName()
{
    return Name;
}

FText UInteractable_Object_Widget::PrintName()
{
    return FText::FromString(Name);
}
