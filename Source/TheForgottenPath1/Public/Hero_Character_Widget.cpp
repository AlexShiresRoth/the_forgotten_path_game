// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero_Character_Widget.h"
#include "TheForgottenPath1/TheForgottenPath1Character.h"

void UHero_Character_Widget::SetCharacterHealth()
{
    ATheForgottenPath1Character *PlayerCharacter = Cast<ATheForgottenPath1Character>(GetOwningPlayerPawn());
    if (PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is valid %s"), *PlayerCharacter->GetName());
    }
}
