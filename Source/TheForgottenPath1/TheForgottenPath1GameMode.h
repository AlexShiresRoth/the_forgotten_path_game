// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheForgottenPath1GameMode.generated.h"

UCLASS(minimalapi)
class ATheForgottenPath1GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATheForgottenPath1GameMode();
};
