// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AEnemyAIController::AEnemyAIController()
{
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AEnemyAIController::StartBehaviorTree(UBehaviorTree *BehaviorTree)
{
    if (BehaviorTree && BehaviorTreeComponent && BlackboardComponent)
    {
        BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

        BehaviorTreeComponent->StartTree(*BehaviorTree);
    }
}