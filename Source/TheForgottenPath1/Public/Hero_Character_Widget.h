// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hero_Character_Widget.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API UHero_Character_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Character Data")
	void SetCharacterHealth();

	// this variable is causing issues, need to probably assign it in blueprint and updated it in the cpp
	// health will have to be dependent on class and stats
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character Data")
	float Health = 10.f;
};