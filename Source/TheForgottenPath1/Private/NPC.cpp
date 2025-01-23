// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/NPC.h"
#include "../Public/DialogWidget.h"

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
    if (DialogWidget)
    {
        UDialogWidget *Dialog = CreateWidget<UDialogWidget>(GetWorld(), DialogWidget);

        if (Dialog)
        {
            Dialog->AddToViewport();
        }
    }
}
