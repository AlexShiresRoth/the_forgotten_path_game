// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/NPC.h"

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
    UE_LOG(LogTemp, Warning, TEXT("NPC Dialog Started with %s"), *GetName());
}
