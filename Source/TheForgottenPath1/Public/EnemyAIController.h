// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.generated.h"

/**
 *
 */

UCLASS()
class THEFORGOTTENPATH1_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	virtual ~AEnemyAIController() override = default;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent *BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent *BlackboardComponent;

	void StartBehaviorTree(UBehaviorTree *BehaviorTree);
};
