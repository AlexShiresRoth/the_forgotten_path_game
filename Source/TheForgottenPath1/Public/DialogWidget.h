// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "DialogWidget.generated.h"

/**
 *
 */
class UNPC_Dialog_Text_Widget;
class UPlayer_Choices_Dialog_Widget;
struct FDialogNode;
UCLASS()
class THEFORGOTTENPATH1_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox *NPCDialogScrollBox;

	UPROPERTY(meta = (BindWidget))
	UScrollBox *PlayerChoicesScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSubclassOf<UNPC_Dialog_Text_Widget> NPCDialogTextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSubclassOf<UPlayer_Choices_Dialog_Widget> PlayerChoicesDialogWidget;

public:
	UFUNCTION()
	void UpdateDialog(const TArray<FDialogChoice> &NPCDialogLines, const TArray<FDialogChoice> &PlayerChoices);
};
