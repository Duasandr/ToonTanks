// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
	Tank = nullptr;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		FVector const CurrentLocation = GetActorLocation();
		FVector const TankLocation    = Tank->GetActorLocation();
		double  const Distance		  = FVector::Dist(TankLocation, CurrentLocation);

		if (Distance < AreaOffEffectRadius)
		{
			FVector const LookAtTarget = Tank->GetActorLocation();
			RotateTurret(LookAtTarget, DeltaTime);
		}
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
