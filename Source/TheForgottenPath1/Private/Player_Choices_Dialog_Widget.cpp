// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Choices_Dialog_Widget.h"

void UPlayer_Choices_Dialog_Widget::SetPlayerChoicesText(FString Text)
{
    if (Text != "")
    {
        PlayerChoicesText = Text;
    }
}
