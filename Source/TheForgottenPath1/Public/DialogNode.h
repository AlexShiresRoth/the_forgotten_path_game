#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "DialogNode.generated.h"

USTRUCT(BlueprintType)
struct FDialogChoice
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FString NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    TArray<FString> DialogLines;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FName NextNodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    TArray<FString> Conditions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    TArray<FString> Effects;
};

USTRUCT(BlueprintType)
struct FDialogNode : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FName NPCID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FName NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    FString NPCInitialText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    TArray<FDialogChoice> NPCResponses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
    TArray<FDialogChoice> PlayerChoices;
};
