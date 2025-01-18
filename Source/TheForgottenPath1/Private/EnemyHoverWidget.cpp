// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHoverWidget.h"
#include "EnemyCharacter.h"

void UEnemyHoverWidget::SetEnemyData(AEnemyCharacter *EnemyCharacter)
{
    if (EnemyCharacter)
    {
        EnemyName = EnemyCharacter->EnemyName;
        EnemyHealth = EnemyCharacter->GetCharacterCurrentHealth();
    }
}