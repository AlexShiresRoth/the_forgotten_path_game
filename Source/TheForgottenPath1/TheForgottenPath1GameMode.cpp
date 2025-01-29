// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheForgottenPath1GameMode.h"
#include "TheForgottenPath1Character.h"
#include "UObject/ConstructorHelpers.h"

ATheForgottenPath1GameMode::ATheForgottenPath1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATheForgottenPath1GameMode::BeginPlay()
{
	Super::BeginPlay();
}
