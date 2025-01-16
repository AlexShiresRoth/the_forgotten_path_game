// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/EnemyHoverWidget.h"

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    USkeletalMeshComponent *SkelMesh = GetMesh();
    if (SkelMesh)
    {
        // Enable cursor over events
        SkelMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SkelMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
        SkelMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

        // Bind the OnBeginCursorOver event
        SkelMesh->OnBeginCursorOver.AddDynamic(this, &AEnemyCharacter::ShowEnemyName);
        SkelMesh->OnEndCursorOver.AddDynamic(this, &AEnemyCharacter::HideEnemyName);
    }
}

void AEnemyCharacter::ShowEnemyName(UPrimitiveComponent *TouchedComponent)
{
    if (EnemyHoverWidgetClass)
    {
        EnemyHoverWidgetInstance = CreateWidget<UEnemyHoverWidget>(GetWorld(), EnemyHoverWidgetClass);

        if (EnemyHoverWidgetInstance)
        {

            UEnemyHoverWidget *EnemyHoverWidget = Cast<UEnemyHoverWidget>(EnemyHoverWidgetInstance);

            if (EnemyHoverWidget)
            {
                UE_LOG(LogTemplateCharacter, Warning, TEXT("Enemy Name: %s"), *EnemyName);
                EnemyHoverWidget->SetEnemyData(this);
                EnemyHoverWidget->AddToViewport();

                FVector MeshLocation = GetActorLocation();

                FVector2D ScreenLocation;

                UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), MeshLocation, ScreenLocation);

                EnemyHoverWidget->SetPositionInViewport(ScreenLocation);
            }
        }
    }
}

void AEnemyCharacter::HideEnemyName(UPrimitiveComponent *TouchedComponent)
{
    if (EnemyHoverWidgetInstance)
    {
        EnemyHoverWidgetInstance->RemoveFromParent();
        EnemyHoverWidgetInstance = nullptr;
    }
}
