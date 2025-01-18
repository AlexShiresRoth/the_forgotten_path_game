// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHoverWidget.generated.h"

/**
 *
 */
class AEnemyCharacter;
UCLASS()
class THEFORGOTTENPATH1_API UEnemyHoverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	FString EnemyName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemyHealth;

	UFUNCTION()
	void SetEnemyData(AEnemyCharacter *EnemyCharacter);
};
