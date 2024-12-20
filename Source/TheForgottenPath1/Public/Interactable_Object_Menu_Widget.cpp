#include "Interactable_Object_Menu_Widget.h"
#include "Interactable_Object_Widget.h"

void UInteractable_Object_Menu_Widget::HandleCloseButtonClicked()
{
    OnCloseButtonClicked.Broadcast();
}

FText UInteractable_Object_Menu_Widget::GetObjectNameFromInteractableObject() const
{
    UInteractable_Object_Widget *InteractableObjectWidget = Cast<UInteractable_Object_Widget>(InteractableObjectWidgetReference);

    if (InteractableObjectWidget)
    {
        FString ObjectName = InteractableObjectWidget->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Object Name: %s"), *ObjectName);
        return FText::FromString(ObjectName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cast failed, invalid reference"));
    }

    // Return a default text if the interactable object is null
    return FText::FromString(TEXT("Unknown Object"));
}
