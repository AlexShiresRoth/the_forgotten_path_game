// Fill out your copyright notice in the Description page of Project Settings.

#include "Forgotten_Path_GM.h"
#include "DialogManager.h"

void AForgotten_Path_GM::BeginPlay()
{
    Super::BeginPlay();

    if (!DialogManager && DialogManagerClass)
    {
        DialogManager = GetWorld()->SpawnActor<ADialogManager>(DialogManagerClass);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DialogManager is null"));
    }
}
