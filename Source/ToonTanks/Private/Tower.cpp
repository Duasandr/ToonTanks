// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"

ATower::ATower()
{
	Tank = nullptr;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector const LookAtTarget = Tank->GetActorLocation();
	RotateTurret(LookAtTarget, DeltaTime);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
