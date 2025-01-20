// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TheForgottenPath1Character.h"
#include "NPC.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API ANPC : public ATheForgottenPath1Character
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void StartDialog();
};
