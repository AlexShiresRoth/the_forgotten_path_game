// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/NPC.h"
#include "../Public/DialogWidget.h"
#include "Forgotten_Path_GM.h"
#include "Dialog_Manager.h"

void ANPC::BeginPlay()
{

    Super::BeginPlay();

    USkeletalMeshComponent *SkelMesh = GetMesh();

    if (SkelMesh)
    {
        // Enable cursor over events
        SkelMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SkelMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
        SkelMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    }
}

void ANPC::StartDialog()
{
    AForgotten_Path_GM *GameMode = Cast<AForgotten_Path_GM>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->DialogManager->StartDialog(NPCID);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameMode is null"));
    }
}
