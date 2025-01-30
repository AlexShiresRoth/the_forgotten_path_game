// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPC_Dialog_Text_Widget.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API UNPC_Dialog_Text_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FString DialogText;

public:
	UFUNCTION()
	void SetDialogText(FString Text);
};
