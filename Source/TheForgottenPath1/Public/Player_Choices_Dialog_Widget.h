// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player_Choices_Dialog_Widget.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API UPlayer_Choices_Dialog_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FString PlayerChoicesText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialog")
	FName NextNodeID;

public:
	UFUNCTION()
	void SetPlayerChoicesText(FString Text, FName ChoiceNextNodeID);

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void ContinueDialogBasedOnPlayerChoice();
};
