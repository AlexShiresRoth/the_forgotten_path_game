#include "Interactable_Object_Menu_Widget.h"

void UInteractable_Object_Menu_Widget::HandleCloseButtonClicked()
{
    OnCloseButtonClicked.Broadcast();
}
