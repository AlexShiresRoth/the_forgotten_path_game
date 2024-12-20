// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable_Object_Widget.h"
#include "Interactable_Object_Menu_Widget.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClickedDelegate);

class UInteractable_Object_Widget;
UCLASS()
class THEFORGOTTENPATH1_API UInteractable_Object_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HandleCloseButtonClicked();

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnCloseButtonClickedDelegate OnCloseButtonClicked;

	UFUNCTION(BlueprintPure, Category = "Object Interaction")
	FText GetObjectNameFromInteractableObject() const;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Interaction")
	// TSubclassOf<UInteractable_Object_Widget> InteractableObjectWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Interaction")
	UInteractable_Object_Widget *InteractableObjectWidgetReference;
};
