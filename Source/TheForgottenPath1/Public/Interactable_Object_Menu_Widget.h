// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable_Object_Menu_Widget.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClickedDelegate);

UCLASS()
class THEFORGOTTENPATH1_API UInteractable_Object_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HandleCloseButtonClicked();

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnCloseButtonClickedDelegate OnCloseButtonClicked;
};
