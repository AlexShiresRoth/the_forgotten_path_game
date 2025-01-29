// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Dialog_Manager.h"
#include "Forgotten_Path_GM.generated.h"

/**
 *
 */
UCLASS()
class THEFORGOTTENPATH1_API AForgotten_Path_GM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Manager")
	TSubclassOf<ADialog_Manager> DialogManagerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialog Manager")
	ADialog_Manager *DialogManager;
};
