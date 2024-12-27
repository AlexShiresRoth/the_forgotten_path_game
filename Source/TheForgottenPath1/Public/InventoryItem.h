// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS(Blueprintable, BlueprintType)
class THEFORGOTTENPATH1_API AInventoryItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int32 ItemID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
