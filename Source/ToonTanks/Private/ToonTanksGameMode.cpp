// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (auto * PlayerController = Tank->GetPlayerController())
		{
			Tank->DisableInput(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}
	}
	else if (auto * Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();	
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
