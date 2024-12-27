// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = "Not Defined";
	ItemDescription = "Not Defined";
	Quantity = 1;
	Image = nullptr;
	Value = 1;
	ItemID = 1;
	ItemMesh = nullptr;
	// TODO extend this to add more properties, say if the item is a weapon, armor, etc
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
