// Fill out your copyright notice in the Description page of Project Settings.

#include "Forgotten_Path_GM.h"
#include "Dialog_Manager.h"

void AForgotten_Path_GM::BeginPlay()
{
    Super::BeginPlay();

    if (!DialogManager && DialogManagerClass)
    {
        DialogManager = GetWorld()->SpawnActor<ADialog_Manager>(DialogManagerClass);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Dialog_Manager is null"));
    }
}
