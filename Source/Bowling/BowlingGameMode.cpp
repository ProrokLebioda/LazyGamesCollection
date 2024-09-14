// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingGameMode.h"

ABowlingGameMode::ABowlingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_BowlingBall"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
