// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
