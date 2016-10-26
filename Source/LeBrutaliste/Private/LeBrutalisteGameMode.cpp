// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "LeBrutaliste.h"
#include "LeBrutalisteGameMode.h"
#include "LeBrutalisteCharacter.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Controller.h"

ALeBrutalisteGameMode::ALeBrutalisteGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_LeBrutalisteCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default HUD class to our Blueprinted HUD Class
	static ConstructorHelpers::FClassFinder<AHUD> AHUDBPClass(TEXT("/Game/Blueprints/BP_LeBrutalisteHUD"));
	if (AHUDBPClass.Class != NULL)
	{
		HUDClass = AHUDBPClass.Class;
	}

	// set default controller class to our Blueprinted controller Class
	static ConstructorHelpers::FClassFinder<APlayerController> APlayerControllerClass(TEXT("/Game/Blueprints/BP_LeBrutalisteController"));
	if (APlayerControllerClass.Class != NULL)
	{
		PlayerControllerClass = APlayerControllerClass.Class;
	}
}
