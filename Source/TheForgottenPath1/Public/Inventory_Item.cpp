// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory_Item.h"

// Sets default values
AInventory_Item::AInventory_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventory_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventory_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

