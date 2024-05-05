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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Data")
	float CharacterHealth = 10.f;
};
