// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable_Object_Menu_Widget.generated.h"

/**
 *
 */

UCLASS()
class THEFORGOTTENPATH1_API UInteractable_Object_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UPROPERTY(BlueprintAssignable, Category = "Widget Events")
	// FButtonClickedDelegate OnButtonClicked;

	// Function to handle button click event
	UFUNCTION(BlueprintCallable)
	void HandleButtonClick();
};
