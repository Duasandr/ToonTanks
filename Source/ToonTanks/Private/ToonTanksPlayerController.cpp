// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool const bPlayerEnabled)
{
	if (APawn * Pawn = GetPawn())
	{
		if (bPlayerEnabled)
		{
			Pawn->EnableInput(this);
		}
		else
		{
			Pawn->DisableInput(this);
		}
		bShowMouseCursor = bPlayerEnabled;
	}
}
