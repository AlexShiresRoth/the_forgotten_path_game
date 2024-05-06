// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero_Character_Widget.h"
#include "TheForgottenPath1/TheForgottenPath1Character.h"

void UHero_Character_Widget::NativeConstruct()
{
    Super::NativeConstruct();

    // Need to get current health at start
    ATheForgottenPath1Character *Character = Cast<ATheForgottenPath1Character>(GetOwningPlayerPawn());
    if (Character)
    {
        Health = Character->GetCharacterCurrentHealth();
    }
}

void UHero_Character_Widget::UpdateHealthUI(float HealthValue)
{
    Health = HealthValue;
}
