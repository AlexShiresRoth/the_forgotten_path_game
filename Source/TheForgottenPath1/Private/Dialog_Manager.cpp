// Fill out your copyright notice in the Description page of Project Settings.

#include "Dialog_Manager.h"
#include "DialogWidget.h"

// Sets default values
ADialog_Manager::ADialog_Manager()
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
void ADialog_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADialog_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialog_Manager::StartDialog(FName NPCID)
{
	if (DialogWidgetClass && !DialogWidgetInstance)
	{
		DialogWidgetInstance = CreateWidget<UDialogWidget>(GetWorld(), DialogWidgetClass);

		if (DialogWidgetInstance && DialogDataTable)
		{
			DialogWidgetInstance->AddToViewport();

			const FDialogNode *RowData = DialogDataTable->FindRow<FDialogNode>(NPCID, TEXT("Looking for Dialog Node"));

			if (RowData)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Dialog Node %s"), *RowData->NodeID.ToString());

				DialogWidgetInstance->UpdateDialog(RowData->NPCResponses, RowData->PlayerChoices);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Did not find Dialog Node %s"), *NPCID.ToString());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NPCID is null"));
	}
}

void ADialog_Manager::DisplayDialog(FName DialogID)
{
}
