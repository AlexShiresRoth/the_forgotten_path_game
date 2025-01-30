// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogWidget.h"
#include "DialogNode.h"
#include "NPC_Dialog_Text_Widget.h"
#include "Player_Choices_Dialog_Widget.h"

void UDialogWidget::UpdateDialog(const TArray<FDialogChoice> &NPCDialogLines, const TArray<FDialogChoice> &PlayerChoices)
{

    if (!NPCDialogScrollBox || !PlayerChoicesScrollBox)
    {
        UE_LOG(LogTemp, Error, TEXT("Scroll boxes are not set up in the DialogWidget!"));
        return;
    }

    // Clear existing children from both scroll boxes to refresh dialog
    NPCDialogScrollBox->ClearChildren();
    PlayerChoicesScrollBox->ClearChildren();

    for (auto Line : NPCDialogLines)
    {
        for (auto DialogLine : Line.DialogLines)
        {
            UNPC_Dialog_Text_Widget *DialogTextWidget = CreateWidget<UNPC_Dialog_Text_Widget>(this, NPCDialogTextWidget);

            if (DialogTextWidget)
            {

                DialogTextWidget->SetDialogText(DialogLine);

                NPCDialogScrollBox->AddChild(DialogTextWidget);
            }
        }
    }

    for (auto Line : PlayerChoices)
    {
        for (auto DialogLine : Line.DialogLines)
        {
            UPlayer_Choices_Dialog_Widget *PlayerChoicesWidget = CreateWidget<UPlayer_Choices_Dialog_Widget>(this, PlayerChoicesDialogWidget);

            if (PlayerChoicesWidget)
            {
                PlayerChoicesWidget->SetPlayerChoicesText(DialogLine);

                PlayerChoicesScrollBox->AddChild(PlayerChoicesWidget);
            }
        }
    }
}