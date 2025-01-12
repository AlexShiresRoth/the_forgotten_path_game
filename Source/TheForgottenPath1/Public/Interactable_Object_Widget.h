// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable_Object_Widget.generated.h"

/**
 * This is just displaying the object name when mouse is over the interactable object
 */
UCLASS()
class THEFORGOTTENPATH1_API UInteractable_Object_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Object Data")
	FString Name;

	void SetCustomInteractableObjectData(FString ObjectTitle, int32 ObjectID);
};
