// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortalSystemGameMode.h"
#include "PortalSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortalSystemGameMode::APortalSystemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
