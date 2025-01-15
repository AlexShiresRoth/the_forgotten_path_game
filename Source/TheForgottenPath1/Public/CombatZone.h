// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "../Public/EnemyCharacter.h"
#include "CombatZone.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API ACombatZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Zone")
	bool bIsInCombatZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Zone")
	TArray<AEnemyCharacter *> EnemiesInCombatZone;

	UFUNCTION()
	void OnPlayerEnterCombatZone(AActor *OverlappedActor, AActor *OtherActor);

	UFUNCTION()
	void OnPlayerExitCombatZone(AActor *OverlappedActor, AActor *OtherActor);

protected:
	void GetEnemiesInCombatZone(AActor *OverlappedActor, AActor *OtherActor);
};
