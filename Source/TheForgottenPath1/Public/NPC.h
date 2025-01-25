// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TheForgottenPath1Character.h"
#include "NPC.generated.h"

/**
 *
 */
class UDialogWidget;
UCLASS()
class THEFORGOTTENPATH1_API ANPC : public ATheForgottenPath1Character
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	// This is used to help find in the data table which dialg to reference for this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FName NPCID;

public:
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void StartDialog();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSubclassOf<UDialogWidget> DialogWidget;

public:
	FName GETNPCID() const { return NPCID; }
};
