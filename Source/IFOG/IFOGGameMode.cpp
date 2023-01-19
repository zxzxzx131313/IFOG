// Copyright Epic Games, Inc. All Rights Reserved.

#include "IFOGGameMode.h"
#include "IFOGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIFOGGameMode::AIFOGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprint/IFOGCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
