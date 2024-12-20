// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable_Object_Menu_Widget.generated.h"

/**
 * A widget that displays information about an interactable object
 * and allows interaction through UI elements like buttons.
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClickedDelegate);

UCLASS()
class THEFORGOTTENPATH1_API UInteractable_Object_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Called when the close button is clicked */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HandleCloseButtonClicked();

	/** Event triggered when the close button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnCloseButtonClickedDelegate OnCloseButtonClicked;

	/** The name of the interactable object, shown in the UI */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Object Data")
	FString ObjectName;

	void SetCustomInteractableObjectData(FString ObjectTitle, int32 ObjectID);
};
