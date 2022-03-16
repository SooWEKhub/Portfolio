// Copyright Piotr Sowka, 2022

#include "MineSWR.h"
#include "Modules/ModuleManager.h"


IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, MineSWR, "MineSWR");

int32 DiffLevel = 1;
FString MapLevel;
