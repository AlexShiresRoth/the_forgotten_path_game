// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TheForgottenPath1Character.h"
#include "Components/PrimitiveComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyCharacter.generated.h"

/**
 *
 */

class UEnemyHoverWidget;
UCLASS()
class THEFORGOTTENPATH1_API AEnemyCharacter : public ATheForgottenPath1Character
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FString EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy UI")
	TSubclassOf<UEnemyHoverWidget> EnemyHoverWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy UI")
	UEnemyHoverWidget *EnemyHoverWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy AI")
	UBehaviorTree *EnemyBehaviorTreeAsset;

public:
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void ShowEnemyName(UPrimitiveComponent *TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void AttackEnemy();

	UFUNCTION()
	void UpdateSpeed(float NewSpeed);

	UFUNCTION()
	void HideEnemyName(UPrimitiveComponent *TouchedComponent);

protected:
	void HandleEnemyDeath();

	void UpdateEnemyWidgetData();
};
