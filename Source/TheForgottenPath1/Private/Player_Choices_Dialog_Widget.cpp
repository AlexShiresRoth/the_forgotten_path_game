// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Choices_Dialog_Widget.h"
#include "DialogManager.h"
#include "Forgotten_Path_GM.h"

void UPlayer_Choices_Dialog_Widget::SetPlayerChoicesText(FString Text, FName ChoiceNextNodeID)
{
    if (Text != "" && !ChoiceNextNodeID.IsNone())
    {
        PlayerChoicesText = Text;

        NextNodeID = ChoiceNextNodeID;
    }
}

// TODO call the dialog manager to continue the dialog
void UPlayer_Choices_Dialog_Widget::ContinueDialogBasedOnPlayerChoice()
{
    if (PlayerChoicesText != "" && !NextNodeID.IsNone())
    {
        AForgotten_Path_GM *GameMode = Cast<AForgotten_Path_GM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->DialogManager->ContinueDialog(NextNodeID);
        }
    }
}