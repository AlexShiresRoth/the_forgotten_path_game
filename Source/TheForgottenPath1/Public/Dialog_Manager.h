// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogNode.h"
#include "DialogWidget.h"
#include "Dialog_Manager.generated.h"

UCLASS()
class THEFORGOTTENPATH1_API ADialog_Manager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialog_Manager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	UDataTable *DialogDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	TSubclassOf<UDialogWidget> DialogWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartDialog(FName NPCID);

	void ContinueDialog(FName NextNodeID);

	void EndDialog();

private:
	UDialogWidget *DialogWidgetInstance;

	FDialogNode *CurrentDialogNode;
};
