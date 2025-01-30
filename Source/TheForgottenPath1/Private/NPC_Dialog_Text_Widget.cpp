// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Dialog_Text_Widget.h"

void UNPC_Dialog_Text_Widget::SetDialogText(FString Text)
{
    if (Text != "")
    {
        DialogText = Text;
    }
}
