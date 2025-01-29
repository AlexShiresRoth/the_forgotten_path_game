// Fill out your copyright notice in the Description page of Project Settings.

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DO NOT USE THIS ONE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "DialogManager.h"
#include "DialogWidget.h"

// Sets default values
ADialogManager::ADialogManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DialogDataTable = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> DialogWidgetBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Dialog_Widget"));

	// okay this was called but the dialog widget is never found
	if (DialogWidgetBPClass.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("DialogWidget class Found %s"), *DialogWidgetBPClass.Class->GetName());
		DialogWidgetClass = DialogWidgetBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DialogWidget Object Not Found"));
	}
}

// Called when the game starts or when spawned
void ADialogManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADialogManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TODO case dialog instance here to handle UI dialog stuff
void ADialogManager::StartDialog(FName NPCID)
{
	if (DialogWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("NPC ID: %s"), *NPCID.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NPCID is null"));
	}
}

void ADialogManager::DisplayDialog(FName DialogID)
{
}