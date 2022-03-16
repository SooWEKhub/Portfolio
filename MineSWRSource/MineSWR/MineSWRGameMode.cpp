// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSWRGameMode.h"
#include "MineSWRPlayerController.h"
#include "MineSWRPawn.h"

AMineSWRGameMode::AMineSWRGameMode()
{
	// no pawn by default
	DefaultPawnClass = AMineSWRPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AMineSWRPlayerController::StaticClass();
}
