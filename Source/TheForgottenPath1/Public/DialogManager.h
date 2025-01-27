// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogNode.h"
#include "DialogWidget.h"
#include "DialogManager.generated.h"

UCLASS(BlueprintType)
class THEFORGOTTENPATH1_API ADialogManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogManager();

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

	void DisplayDialog(FName DialogID);

private:
	UDialogWidget *DialogWidgetInstance;

	FDialogNode *CurrentDialogNode;
};
