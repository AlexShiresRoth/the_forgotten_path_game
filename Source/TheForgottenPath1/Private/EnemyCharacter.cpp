// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../Public/EnemyHoverWidget.h"

AEnemyCharacter::AEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AEnemyAIController::StaticClass();
}

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

    // initialize the enemy AI controller
    AEnemyAIController *EnemyAIController = Cast<AEnemyAIController>(GetController());

    if (EnemyAIController)
    {
        UE_LOG(LogTemplateCharacter, Warning, TEXT("Enemy AI Controller created"));
        EnemyAIController->StartBehaviorTree(EnemyBehaviorTreeAsset);
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
                EnemyHoverWidget->SetEnemyData(this);
                EnemyHoverWidget->AddToViewport();

                FVector MeshLocation = GetMesh()->Bounds.Origin + FVector(0, 0, GetMesh()->Bounds.BoxExtent.Z);

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

void AEnemyCharacter::AttackEnemy()
{
    if (this != nullptr)
    {
        // TODO: this is the start of the attack on an enemy logic, super basic for now
        this->SetCharacterCurrentHealth(this->GetCharacterCurrentHealth() - 10.f);
    }

    // Update the enemy widget data ie: health and alive status
    this->UpdateEnemyWidgetData();

    // We need to update the health UI here

    if (this->GetCharacterCurrentHealth() <= 0.f)
    {
        this->HandleEnemyDeath();
    }
}

void AEnemyCharacter::UpdateEnemyWidgetData()
{
    if (EnemyHoverWidgetInstance)
    {

        UEnemyHoverWidget *EnemyHoverWidget = Cast<UEnemyHoverWidget>(EnemyHoverWidgetInstance);

        if (EnemyHoverWidget)
        {
            EnemyHoverWidget->SetEnemyData(this);
        }
    }
    else
    {
        UE_LOG(LogTemplateCharacter, Warning, TEXT("Enemy Hover Widget Instance is null"));
    }
}

void AEnemyCharacter::HandleEnemyDeath()
{

    this->bIsDead = true;
    this->EnterRagdoll();
    this->SetCharacterCurrentHealth(0.f);
}
