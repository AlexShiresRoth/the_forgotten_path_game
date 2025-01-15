// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatZone.h"
#include "../Public/PlayerCharacter.h"
#include "../Public/EnemyCharacter.h"
#include "GameFramework/Actor.h"

void ACombatZone::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &ACombatZone::OnPlayerEnterCombatZone);
    OnActorEndOverlap.AddDynamic(this, &ACombatZone::OnPlayerExitCombatZone);
}

void ACombatZone::GetEnemiesInCombatZone(AActor *OverlappedActor, AActor *OtherActor)
{
    UE_LOG(LogTemp, Warning, TEXT("FIRST: Getting enemies in combat zone"));

    TArray<AActor *> OverlappingActors;
    OverlappedActor->GetOverlappingActors(OverlappingActors);

    for (AActor *Actor : OverlappingActors)
    {
        UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *Actor->GetName());

        if (AEnemyCharacter *EnemyCharacter = Cast<AEnemyCharacter>(Actor))
        {
            UE_LOG(LogTemp, Warning, TEXT("SECOND: Enemy character exists"));

            if (EnemyCharacter && !EnemiesInCombatZone.Contains(EnemyCharacter))
            {
                EnemiesInCombatZone.Add(EnemyCharacter);

                UE_LOG(LogTemp, Warning, TEXT("Enemy added to combat zone %s"), *EnemyCharacter->GetName());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Enemy already in combat zone %s"), *EnemyCharacter->GetName());
            }
        }
    }
}

void ACombatZone::OnPlayerEnterCombatZone(AActor *OverlappedActor, AActor *OtherActor)
{
    if (APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
    {
        UE_LOG(LogTemp, Log, TEXT("%s entered the combat zone!"), *PlayerCharacter->GetName());
        GetEnemiesInCombatZone(OverlappedActor, OtherActor); // Detect enemy characters in combat zone
        PlayerCharacter->EnterCombat();                      // Call a function to start combat logic
    }
}

void ACombatZone::OnPlayerExitCombatZone(AActor *OverlappedActor, AActor *OtherActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Player exited combat zone"));
}