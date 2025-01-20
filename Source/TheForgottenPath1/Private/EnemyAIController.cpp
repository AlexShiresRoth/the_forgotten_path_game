// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Public/EnemyCharacter.h"

AEnemyAIController::AEnemyAIController()
{
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    AEnemyCharacter *EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());

    if (EnemyCharacter)
    {
        UE_LOG(LogTemplateCharacter, Warning, TEXT("Enemy AI Controller created"));
        StartBehaviorTree(EnemyCharacter->EnemyBehaviorTreeAsset);
    }

    SetRandomPatrolLocation();

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIController::SetRandomPatrolLocation, 5.f, true);
}

void AEnemyAIController::StartBehaviorTree(UBehaviorTree *BehaviorTree)
{
    if (BehaviorTree && BehaviorTreeComponent && BlackboardComponent)
    {
        BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

        BehaviorTreeComponent->StartTree(*BehaviorTree);
    }
}

void AEnemyAIController::SetRandomPatrolLocation()
{
    FVector Origin = GetPawn()->GetActorLocation();
    FNavLocation NavLocation;

    UNavigationSystemV1 *NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

    if (NavSys && NavSys->GetRandomPointInNavigableRadius(Origin, 1000.f, NavLocation))
    {
        // Set the random location as the target location in the blackboard
        BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), NavLocation.Location);

        ACharacter *Enemy = Cast<ACharacter>(GetPawn());

        if (Enemy)
        {
            FVector Velocity = Enemy->GetVelocity();
            float Speed = Velocity.Size();

            Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.f;
        }

        MoveToLocation(NavLocation.Location);
    }
}
