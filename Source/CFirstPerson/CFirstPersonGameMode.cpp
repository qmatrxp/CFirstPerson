// Copyright Epic Games, Inc. All Rights Reserved.

#include "CFirstPersonGameMode.h"
#include "CFirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACFirstPersonGameMode::ACFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
